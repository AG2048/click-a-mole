#ifndef MOLE_CONTROLLER_H
#define MOLE_CONTROLLER_H

class MoleController {
    public:
        MoleController();

        ~MoleController();

        void init();

        void addMole(Mole* mole);

        void updateAll();

        void updateMole(int index);

        void setHealth(int index, int curr_hp, int max_hp);

        void resetAll();
        
    private:
        vector<Mole*> moles;
}

#endif // MOLE_CONTROLLER_H
