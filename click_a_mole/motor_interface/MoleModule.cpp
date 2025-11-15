#include "MoleModule.h"

MoleModule::MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorAddr) 
    : pulPin(pulPin), dirPin(dirPin), buttonPin(buttonPin), sensorAddr(sensorAddr),
    motor(pulPin, dirPin), sensor(sensorAddr) {
}

void MoleModule::init() {
    // Run init functions for I2C
}

void MoleModule::update(int& isPressed) {
    currAngle = sensor.readAngle();
    isPressed = button.debounce();

    {motorDir, motorSteps} = func(currAngle, targetAngle);
}

void MoleModule::handleISR() {
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

void MoleModule::setHp(int currHp, int maxHp) {
    targetAngle = func(currHp, maxHp);
}
