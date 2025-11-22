#include "MoleController.h"

ISR(TIMER1_COMPA_vect) { // 100us
    for (MoleModule* x : MoleController::moles) {
        x->stepUpdate();
    }
}

MoleController::MoleController() {
    moleCount = 0;
    moles = nullptr;
}

MoleController::~MoleController() {
    for (MoleModule* x : moles) {
        delete x;
    }
    delete[] moles;
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

    // TODO: Check if timer is same as millis timer

    Wire.begin();
    mux.begin(Wire);
    mux.closeAll();
}

void MoleController::addModule(MoleModule* mole) {
    MoleModule** newMoles = new MoleModule*[moleCount + 1];

    for (int i = 0; i < moleCount; i++) {
        newMoles[i] = moles[i];
    }

    delete[] moles;

    moles = newMoles;
    moles[moleCount] = mole;
    
    moleCount++;
}

void MoleController::updateAll() {
    for (MoleModule* x : moles) {
        x->update(&mux);
    }
}

void MoleController::readButtons(int* arr) {
    for (int i = 0; i < moleCount; i++) {
        arr[i] = moles[i]->readButton();
    }
}

void MoleController::setHp(int index, int currHp, int maxHp) {
    moles[index]->setAngle(currHp, maxHp);
}

void MoleController::resetHp() {
    for (MoleModule* x : moles) {
        x->setAngle(0, 1);
    }
}
