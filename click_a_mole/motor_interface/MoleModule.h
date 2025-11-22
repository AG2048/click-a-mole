#ifndef MOLE_MODULE_H
#define MOLE_MODULE_H

struct pin_t {
    uint8_t id;
    volatile uint8_t* port;
    uint8_t bitmask;
};

class MoleModule {
    public:
        MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorID);

        /* 
        * Read button state determine if button pressed since last read, update buttonPressed
        * Read encoder angle (I2C), update currAngle
        * Update motor params (motorDir, motorSteps) based on target vs current angle
        */
        void update();

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

    private:
        TB6600 motor;
        AS5600 sensor;

        pin_t pulPin;
        pin_t dirPin;
        uint8_t buttonPin;
        uint8_t sensorID; // Not the I2C addr, for the bi-mux

        volatile uint8_t motorDir = 0;
        volatile uint32_t motorSteps = 0;
        
        int targetAngle = 0;
        int currAngle = 0;

        int buttonPressed = 0;
}

#endif // MOLE_MODULE_H
