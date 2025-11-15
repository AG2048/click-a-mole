#ifndef MOLE_MODULE_H
#define MOLE_MODULE_H

class MoleModule {
    public:
        MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorAddr);

        void init();

        /* 
        Updates button state to external
        Updates motorDir, motorSteps to internal
        Updates encoderAngle to internal  */
        void update(int& isPressed);

        // Sends pulse to stepper
        void handleISR();

        // Updates mole hp
        void setHp(int currHp, int maxHp);

    private:
        TB6600 motor;
        AS5600 sensor;

        pin_t pulPin;
        pin_t dirPin;
        uint8_t buttonPin;
        uint8_t sensorAddr;

        volatile uint8_t motorDir = 0;
        volatile uint32_t motorSteps = 0;
        
        int targetAngle = 0;
        int currAngle = 0;
}

#endif // MOLE_MODULE_H
