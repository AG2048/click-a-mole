#include "MoleModule.h"

MoleModule::MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorID) 
    : pulPin(pulPin), dirPin(dirPin), buttonPin(buttonPin), sensorID(sensorID),
    motor(pulPin, dirPin), sensor(sensorID) { }

void MoleModule::update() {
    // Get encoder angle value I2C
    // Update currAngle
    // Get current button state
    // Update buttonRS if needed
    // Compute motor vars from curr and target angle (add hysteresis?)
}


int MoleModule::readButton() {
    if (buttonRS) { // RS latch for 'button pressed'
        buttonRS = 0;
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
