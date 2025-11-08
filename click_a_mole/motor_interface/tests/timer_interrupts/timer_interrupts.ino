#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000
#define LED_PIN PB7 // Pin 13
#define T1_LOAD 0
#define T1_CMP 31250

void setup() {
  // Set pin as output
  DDRB |= (1 << LED_PIN);

  // Clear config A reg
  TCCR1A = 0;

  // Clear config B reg
  TCCR1B = 0;

  // Set CTC mode
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);

  // Set prescalar
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  // Set init and final value
  TCNT1 = T1_LOAD;
  OCR1A = T1_CMP;

  // Enable interrupts for OCR1A
  TIMSK1 = (1 << OCIE1A);

  // Enable interrupts globally
  sei();
}

ISR(TIMER1_COMPA_vect) {
  // Flip bit
  PORTB ^= (1 << LED_PIN);
}

void loop() {
  delay(10000);
}