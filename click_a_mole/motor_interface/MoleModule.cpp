#include "MoleModule.h"

MoleModule::MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorID) 
    : pulPin(pulPin), dirPin(dirPin), buttonPin(buttonPin), sensorID(sensorID) {

    // Read initial state of the button
    pinMode(buttonPin, INPUT_PULLUP);
    lastButtonState = digitalRead(buttonPin);  
}

void MoleModule::update(TCA9548A& mux) {
    // Get encoder angle value I2C  
    mux.openChannel(sensorID);
    delayMicroseconds(10);  
    // Update currAngle
    currAngle = sensor.readAngle();
    mux.closeChannel(sensorID);


    // Get current button state
    int currentButtonState = digitalRead(buttonPin);
    
    // Check for state change
    if (currentButtonState != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentButtonState == LOW && lastButtonState == HIGH) {
            buttonPressed = 1;
        }
    }

    lastButtonState = currentButtonState;


    
    // Compute motor dir and motor steps from curr and target angle
    float error = targetAngle - currAngle;

    // find shortest path
    if (error > 180.0) {
        error -= 360.0;
    } else if (error < 180.0) {
        error += 360.0;
    }

    // check if close to target, if close, then done
    if (fabs(error) <= positionTolerance) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {motorSteps = 0;}
        motorDir = 0;
        return;
    }

    // change dir later if needed
    motorDir = (error > 0) ? 1 : 0;

    // calculate steps
    const float stepsPerDegree = (3200/1.8);
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {uint32_t motorSteps = (uint32_t)(fabs(error) * stepsPerDegree);}

    // // adjust speed ???
    // if (fabs(error) > threshold) {
    //     currentStepDelay = fastStepDelay;
    // } else {
    //     currentStepDelay = slowStepDelay;
    // }
}


int MoleModule::readButton() {
    if (buttonPressed) { // RS latch for 'button pressed'
        buttonPressed = 0;
        return true;
    } else {
        return false;
    }
}

void MoleModule::setAngle(int currHp, int maxHp) {
    targetAngle = (currHp / maxHp) * 360; // example function
}

void MoleModule::stepUpdate() {
    if (motorDir) {
        *(dirPin.port) |= dirPin.bitmask;
    } else {
        *(dirPin.port) &= ~(dirPin.bitmask);
    }

    if (motorSteps > 0) {
        *(pulPin.port) ^= pulPin.bitmask;
        motorSteps--;
    }
}
