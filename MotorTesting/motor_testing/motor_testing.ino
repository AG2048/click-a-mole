const int outputPin = 13;   
const int dirPin = 12;

int frequency = 500;         
unsigned long halfPeriod;   

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(dirPin, OUTPUT);  
  Serial.begin(9600);

  halfPeriod = 1000000L / (2 * frequency);
  digitalWrite(dirPin, HIGH);
}

void loop() {
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(halfPeriod);
  digitalWrite(outputPin, LOW);
  delayMicroseconds(halfPeriod);
}