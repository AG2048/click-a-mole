#include "AS5600.h"

AS5600::AS5600() {

}

// initializing AS5600
void AS5600::init() {
    Wire.begin();

    // set read pointer in reg file
    Wire.beginTransmission(addr);
    Wire.write(angleReg);
    Wire.endTransmission();
}

// Read encoder value (0-4095)
int AS5600::readEncoder() {
    Wire.requestFrom(addr, 2);

    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    int encoderVal = ((msb & 0x0F) << 8) | lsb;    // masking

    return encoderVal;
}

// Read angle value (0-360)
float AS5600::readAngle() {
    int encoderVal = readEncoder();
    float degrees = (encoderVal / 4096.0) * 360.0;

    // handles negative values after subtracting offset
    float correctedAngle = fmod(degrees - offset, 360.0);
    if (correctedAngle < 0 ) {
        correctedAngle += 360.0;
    }

    return correctedAngle;
}

// Read current angle and set it as offset
void AS5600::setZeroPos() {
    float currentAngle = readAngle();
    offset = currentAngle;
}