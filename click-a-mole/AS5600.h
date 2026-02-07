#ifndef AS5600_H
#define AS5600_H

#include <Arduino.h>
#include <Wire.h>

class AS5600 {
    public:
        AS5600();

        // Init AS5600 I2C, and set read pointer in regfile
        void init();

        // Read angle value (0-360)
        float readAngle();

        // Set angle offset relative to true magnetic field (turning it to a position and call that 0 in the chip)
        void setZeroPos();
        
    private:
        int addr = 0x36;
        int angleReg = 0x0E;
        float offset = 0.0;

        // Read encoder value (0-4095)
        int readEncoder();
};

#endif // AS5600_H
