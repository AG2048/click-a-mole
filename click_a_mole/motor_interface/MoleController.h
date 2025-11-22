#ifndef MOLE_CONTROLLER_H
#define MOLE_CONTROLLER_H

#include <Wire.h>
#include <TCA9548A.h>
#include "MoleModule.h"

class MoleController {
    public:
        MoleController();

        // Free MoleModule instances in moles vector
        ~MoleController();

        /* 
        * Initialize timer interrupt
        * Initialize bi-mux I2C
        */
        void init();

        // Mallocs an instance of MoleModule, add to moles vector
        void addModule(MoleModule* mole);

        // Call update() on all MoleModules in moles vector
        void updateAll();

        // Returns array of button states from all MoleModules
        void readButtons(int* arr);

        // Call setHp() on MoleModule at index of moles vector
        void setHp(int index, int currHp, int maxHp);

        // Call setHp() on all MoleModules and set to zero
        void resetHp();
        
    private:
        TCA9548A mux;
        vector<MoleModule*> moles;
}

#endif // MOLE_CONTROLLER_H
