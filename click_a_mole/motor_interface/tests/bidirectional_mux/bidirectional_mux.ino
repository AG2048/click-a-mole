#include <Wire.h>
#include <Arduino.h>
#include <TCA9548A.h>

TCA9548A mux;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mux.begin(Wire);
  mux.closeAll();
}

void loop() {
  for(int i = 0; i < 2; i++) {
    mux.openChannel(i);
    delayMicroseconds(10);
    
    Wire.beginTransmission(0x36);
    Wire.write(0x0E);
    Wire.endTransmission();
    
    Wire.requestFrom(0x36, 2);
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    int result = ((msb & 0x0F) << 8) | lsb;
    float degrees = (result / 4096.0) * 360.0;
    
    mux.closeChannel(i);
    
    Serial.print("E");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(degrees);
    Serial.print("°   ");
  }
  Serial.println();
  delay(500);
}