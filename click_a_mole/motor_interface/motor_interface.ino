// setup file for testing

void attachInterrupt() {
  // Clear config A reg
  TCCR1A = 0;

  // Clear config B reg
  TCCR1B = 0;

  // Set CTC mode
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);

  // Set prescalar
  TCCR1B &= ~(1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS10);

  // Set init and final value
  TCNT1 = 0;
  OCR1A = T1_CMPA;

  // Enable interrupts for OCR1A
  TIMSK1 = (1 << OCIE1A);

  // Enable interrupts globally
  sei();
}

ISR(TIMER1_COMPA_vect) { // 100us
  for (int i = 0; i < NUM_MOTORS; i++) {
    moles[i].handleISR();
  }
}

void setup() {
    // Pin mode setup
    attachInterrupt();
}

void loop() {
    delay(10000);
}
