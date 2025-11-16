#include "MoleModule.h"

MoleModule::MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorAddr) 
    : pulPin(pulPin), dirPin(dirPin), buttonPin(buttonPin), sensorAddr(sensorAddr),
    motor(pulPin, dirPin), sensor(sensorAddr) {
}

uint8_t MoleModule::getMotorDir() {
    return motorDir;
}

uint32_t MoleModule::getMotorSteps() {
    return motorSteps;
}

int MoleModule::readButton() {
    if (buttonRS) { // RS latch for 'button pressed'
        buttonRS = 0;
        return true;
    } else {
        return false;
    }
}

void MoleModule::setHp(int currHp, int maxHp) {
    targetAngle = (currHp / maxHp) * 360; // example function
}

// void MoleModule::handleISR() {
//     if (motorDir) {
//         *(dirPin.port) |= dirPin.bitmask;
//     } else {
//         *(dirPin.port) &= ~(dirPin.bitmask);
//     }

//     if (motorSteps > 0) {
//         *(pulPin.port) ^= pulPin.bitmask;
//         motorSteps--;
//     }
// }

void MoleModule::update() {
    // Get encoder angle value I2C
    // Update currAngle
    // Get current button state
    // Update buttonRS if needed
    // Compute motor vars from curr and target angle (add hysteresis?)
}
