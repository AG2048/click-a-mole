#ifndef MOLE_MODULE_H
#define MOLE_MODULE_H

class MoleModule {
    public:
        MoleModule(pin_t pulPin, pin_t dirPin, uint8_t buttonPin, uint8_t sensorAddr);

        // Gets encoder and button state, computes next motor params
        void update();

        // Returns button value and resets RS latched state
        int readButton();

        // Update target angle based on hp
        void setHp(int currHp, int maxHp);

        uint8_t getMotorParams(uint8_t& motorDir, uint32_t& motorSteps); // motorSteps needs to be atomic read

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

        int buttonRS = 0;

        // These three don't have to be separate functions can be in update()
        void setMotorParams();
        int getEncoderAngle();
        int getButtonState();
}

#endif // MOLE_MODULE_H
