#include "MoleController.h"

MoleModule **MoleController::moles = nullptr;
int MoleController::moleCount = 0;

ISR(TIMER1_COMPA_vect)
{ // slow 5ms, fast 100us
    MoleController::stepAll();
}

MoleController::MoleController()
{
}

MoleController::~MoleController()
{
    cli(); // Disable interrupts during destructor
    for (int i = 0; i < moleCount; i++)
    {
        delete moles[i];
    }
    delete[] moles;
    sei();
}

void MoleController::init()
{
    // Wire.begin();
    mux.begin(Wire);
    mux.closeAll();
    Serial.println("MoleController init complete");
}

void MoleController::startTimer()
{
    cli();

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

// IMPORTANT: Must be called before .init()
// Fix this to allocate x2 instead of +1 each time
void MoleController::addModule(MoleModule *mole)
{
    cli();

    MoleModule **newMoles = new MoleModule *[moleCount + 1];

    for (int i = 0; i < moleCount; i++)
    {
        newMoles[i] = moles[i];
    }

    delete[] moles;

    moles = newMoles;
    moles[moleCount] = mole;

    moleCount++;

    sei();

    mole->init();
}

void MoleController::updateAll()
{
    for (int i = 0; i < moleCount; i++)
    {
        moles[i]->update(mux);
    }
}

void MoleController::readButtons(int (&arr)[8])
{
    for (int i = 0; i < moleCount; i++)
    {
        arr[i] = moles[i]->readButton();
    }
}

void MoleController::setHp(int index, int currHp, int maxHp)
{
    moles[index]->setAngle(currHp, maxHp);
}

void MoleController::resetHp()
{
    for (int i = 0; i < moleCount; i++)
    {
        moles[i]->setAngle(0, 1);
    }
}

void MoleController::stepAll()
{
    for (int i = 0; i < moleCount; i++)
    {
        moles[i]->stepUpdate();
    }
}