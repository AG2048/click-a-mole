#ifndef AS5600_H
#define AS5600_H

#include <Arduino.h>

class AS5600 {
    public:
        AS5600(uint8_t addr = 0x36);

        // Init AS5600 I2C, and set read pointer in regfile
        void init();

        // Read encoder value (0-4095)
        int read_encoder();

        // Read angle value (0-360)
        int read_angle();

        // Set angle offset relative to true magnetic field
        void set_zero_pos();
        
    private:
        uint8_t addr;
        float offset;
}

#endif // AS5600_H
