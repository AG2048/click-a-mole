#ifndef TB6600_H
#define TB6600_H

#include <Arduino.h>

#define DEGREE 1.8

class TB6600 {
    public:
        TB6600(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, float stepsPerRev = 200.0);
        void begin();

        void move(long steps);
        void movebyAngle(long angle);
        void stop();

        // speeds
        void setSpeed(float rpm);

        // positions
        void setCurrentPosition(long position);
        long getCurrentPosition();

        // dir pin
        void setDirection(bool direction);
        void invertDirection(bool invert);

        void sqaureWave(int frequency);
        void run();

        // Setters
        void setStepPin(uint8_t stepPin);
        void setDirPin(uint8_t dirPin);
        void setEnablePin(uint8_t enaPin);

    private:
        // pin definitions
        uint8_t _stepPin;
        uint8_t _dirPin;
        uint8_t _enaPin;
};

#endif // TB6600_H
