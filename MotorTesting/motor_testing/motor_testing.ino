#include <Wire.h>

const int outputPin = 13;   
const int dirPin = 12;

int frequency = 500;         
unsigned long halfPeriod;   

void setup() {
  Wire.begin();
  Wire.beginTransmission(0x36);
  Wire.write(0x0E);
  Wire.endTransmission();

  // pinMode(outputPin, OUTPUT);
  // pinMode(dirPin, OUTPUT);  
  Serial.begin(9600);

  // halfPeriod = 1000000L / (2 * frequency);
  // digitalWrite(dirPin, HIGH);
}

void loop() {
  // digitalWrite(outputPin, HIGH);
  // delayMicroseconds(halfPeriod);
  // digitalWrite(outputPin, LOW);
  // delayMicroseconds(halfPeriod);
  // Serial.println("hi");

  Wire.requestFrom(0x36, 2);
  // while(Wire.available()<2) {
  //   Serial.println("11111111");   
  // }
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();
  
  int result = ((msb & 0x0F)<<8) | lsb;
  float degrees = (result / 4096.0) * 360.0;
  Serial.println(degrees);
  delay(500);
  
  
}
