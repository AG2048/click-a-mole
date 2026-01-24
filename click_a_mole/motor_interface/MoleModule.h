#ifndef MOLE_MODULE_H
#define MOLE_MODULE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "AS5600.h"
#include <Wire.h>
#include <TCA9548A.h>

struct pin_t {
    uint8_t id;
    volatile uint8_t* port;
    uint8_t bitmask;
};

class MoleModule {
    public:
        MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorID);

        void init();

        /* 
        * Read button state determine if button pressed since last read, update buttonPressed
        * Read encoder angle (I2C), update currAngle
        * Update motor params (motorDir, motorSteps) based on target vs current angle
        */
        void update(TCA9548A& mux);

        /* 
        * Returns the if button pressed since last read
        * Resets buttonPressed state on function call
        */
        int readButton();

        // Update targetAngle based on function of Hp
        void setAngle(int currHp, int maxHp);

        /*
        * Called in ISR macro in MoleController.cpp
        * Based on (motorDir, motorSteps), update motor control pin registers
        */
        void stepUpdate();
        void setMinVelocity(int minV){ minVelocity = minV; }
        void setMaxVelocity(int maxV){ maxVelocity = maxV; if (maxVelocity < 1) maxVelocity = 1; }


    private:
        AS5600 sensor;

        pin_t pulPin;
        pin_t dirPin;
        uint8_t buttonPin;
        uint8_t sensorID; // Not the I2C addr, for the bi-mux

        volatile int dstVelocity = 1;
        int velocityCounter = 0;
        int minVelocity = 5;
        int maxVelocity = 1;
        
        int targetAngle = 0;
        int currAngle = 0;

        // button
        int buttonPressed = 0; 
        int lastButtonState = HIGH;   
        int stableButtonState = HIGH;
        unsigned long lastDebounceTime = 0;  // last time button state changed
        unsigned long debounceDelay = 10;  

        // motor
        volatile uint8_t motorDir = 0;
        volatile uint32_t motorSteps = 0;
    
        float threshold = 10.0;  // switch to slow speed
        float positionTolerance = 1.8;   
        
        // uint32_t fastStepDelay = 500;    // ms between fast steps ??
        // uint32_t slowStepDelay = 2000;   // ms between slow steps ??
        // uint32_t currentStepDelay = fastStepDelay;
};

#endif // MOLE_MODULE_H
