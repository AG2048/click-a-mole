#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H
class DisplayInterface
{
public:
    void show_score(int current_score);
    void startMole(int ID, int maxHP, unsigned long duration);
    void changeMoleHP(int moleID, int newHP, int maxHP);
    void changeDuration(int moleID, int newDuration);
    void endMole(int moleID, bool isTimeout, bool isHPZero);
    void changeMoleColourMode(int moleID, int newColour);
    unsigned long update_time(unsigned long time);
    void update_heart(int lives);

private:
};
#endif // LED_INTERFACE_H