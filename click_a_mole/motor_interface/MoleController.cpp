#include "MoleController.h"

ISR(TIMER1_COMPA_vect) { // 100us
    for (MoleModule* x : MoleController::moles) {
        x->stepUpdate();
    }
}

MoleController::MoleController() { }

MoleController::~MoleController() {

}

void MoleController::init() {
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

    // TODO: Initialize bi-mux I2C
}

void MoleController::addModule(MoleModule* mole) {

}

void MoleController::updateAll() {

}

void MoleController::readButtons(int* arr) {

}

void MoleController::setHp(int index, int currHp, int maxHp) {

}

void MoleController::resetHp() {

}
