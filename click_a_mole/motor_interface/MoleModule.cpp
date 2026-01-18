#include "MoleModule.h"
#define TOTAL_DEGREES_PER_ROLL 360.0

MoleModule::MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorID) 
    : pulPin(pulPin), dirPin(dirPin), buttonPin(buttonPin), sensorID(sensorID) {

    pinMode(pulPin.id, OUTPUT);
    pinMode(dirPin.id, OUTPUT);

    // Read initial state of the button
    pinMode(buttonPin, INPUT_PULLUP);
    lastButtonState = digitalRead(buttonPin);  

    this->minVelocity = 5;
    this->maxVelocity = 1;

}

void MoleModule::init() {
    sensor.init();
}

void MoleModule::update(TCA9548A& mux) {
    // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {motorSteps = 3200;}
    
    // Get current button state
    int currentButtonState = digitalRead(buttonPin);
    
    // Check for state change
    if (currentButtonState != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentButtonState != stableButtonState) {
            stableButtonState = currentButtonState;
            
            if (stableButtonState == HIGH) {
                buttonPressed = 1;
            }
        }
    }

    lastButtonState = currentButtonState;

    
    // Get encoder angle value I2C  
    // Serial.println("ID " + String(sensorID));
    // Wire.beginTransmission(0x70);
    // Wire.write(0x00);
    // Wire.endTransmission(true);
    mux.openChannel(sensorID);
    // delayMicroseconds(10);  
    // Update currAngle
    sensor.init();
    currAngle = sensor.readAngle();
    mux.closeChannel(sensorID);
    // Serial.print("Angle: ");
    // Serial.println(currAngle);


    // Compute motor dir and motor steps from curr and target angle
    float error = targetAngle - currAngle;

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
    // uint32_t stepsToMove = min(40, (uint32_t)(fabs(error) * stepsPerDegree))
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {motorSteps = (uint32_t)(fabs(error) * stepsPerDegree);}

    // return;
    // calculate dstVelocity
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { dstVelocity = minVelocity + (maxVelocity - minVelocity) / TOTAL_DEGREES_PER_ROLL * error; }
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
    targetAngle = ((double)currHp / maxHp) * TOTAL_DEGREES_PER_ROLL; // example function
}

void MoleModule::stepUpdate() {
    if (motorDir) 
    {
        *(dirPin.port) |= dirPin.bitmask;
    } else {
        *(dirPin.port) &= ~(dirPin.bitmask);
    }

    if (motorSteps > 0){
        velocityCounter++;
        if (velocityCounter >= dstVelocity) 
        { 
            velocityCounter = 0;

            *(pulPin.port) ^= pulPin.bitmask;
            motorSteps--;
        } 
    }
}
