#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define F_CPU 16000000
#define T1_CMPA 1600
#define NUM_MOTORS 2

struct pin_t {
  uint8_t id;
  volatile uint8_t* port;
  uint8_t bitmask;
};

const pin_t PUL_PIN[NUM_MOTORS] = {{22, &PORTA, (1 << PA0)}, {24, &PORTA, (1 << PA2)}}; // 22, 24, 26, 28, 30, 32, 34, 36, 38
const pin_t DIR_PIN[NUM_MOTORS] = {{23, &PORTA, (1 << PA1)}, {25, &PORTA, (1 << PA3)}}; // 23, 25, 27, 29, 31, 33, 35, 37, 39

volatile uint8_t motor_dir[NUM_MOTORS] = {0};
volatile uint16_t motor_hsteps[NUM_MOTORS] = {0}; // Needs atomic writes

void init_motor_int() {
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

void setup() {
  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(PUL_PIN[i].id, OUTPUT);
    pinMode(DIR_PIN[i].id, OUTPUT);
  }

  init_motor_int();
}

/* Possible optimizations if needed
1. Manual loop unrolling
2. Eliminate branching motor_dir
3. Update DIR_PIN on motor_dir update
4. Precompute combined port bitmask
*/
ISR(TIMER1_COMPA_vect) { // 100us
  for (int i = 0; i < NUM_MOTORS; i++) {
    if (motor_dir[i]) {
      *(DIR_PIN[i].port) |= DIR_PIN[i].bitmask;
    } else {
      *(DIR_PIN[i].port) &= ~(DIR_PIN[i].bitmask);
    }

    if (motor_hsteps[i] > 0) {
      *(PUL_PIN[i].port) ^= PUL_PIN[i].bitmask;
      motor_hsteps[i]--;
    }
  }
}

void loop() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    for (int i = 0; i < NUM_MOTORS; i++) {
      motor_dir[i] = !motor_dir[i];
      motor_hsteps[i] += 30000;
    }
  }

  delay(5000);
}