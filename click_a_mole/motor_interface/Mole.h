#ifndef MOLE_H
#define MOLE_H

class Mole {
    public:
        Mole(uint8_t pulPin, uint8_t dirPin, uint8_t sensorAddr);

        void init();

        void update();

        void setHp(int curr_hp, int max_hp);

        int getCurrHp() const;

        int getMaxHp() const;

        void reset();

    private:
        TB6600& motor;
        AS5600& sensor;
        
        uint8_t pulPin;
        uint8_t dirPin;
        uint8_t sensorAddr;

        int curr_hp;
        int max_hp;
}

#endif // MOLE_H
