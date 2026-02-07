#ifndef MOLE_CONTROLLER_H
#define MOLE_CONTROLLER_H

#include "MoleModule.h"

#define T1_CMPA 800
#define TCA9548A_ADDRESS 0x70

class MoleController
{
public:
    MoleController();

    // Free MoleModule instances in moles vector
    ~MoleController();

    /*
     *
     * Initialize bi-mux I2C
     */
    void init();

    // Initialize timer interrupt
    void startTimer();

    // Mallocs an instance of MoleModule, add to moles vector
    void addModule(MoleModule *mole);

    // Call update() on all MoleModules in moles vector
    void updateAll();

    // Returns array of button states from all MoleModules
    void readButtons(int *arr[]);

    // Call setHp() on MoleModule at index of moles vector
    void setHp(int index, int currHp, int maxHp);

    // Call setHp() on all MoleModules and set to zero
    void resetHp();

    // Called in ISR
    static void stepAll();

private:
    TCA9548A mux;

    static MoleModule **moles;
    static int moleCount;
};

#endif // MOLE_CONTROLLER_H
