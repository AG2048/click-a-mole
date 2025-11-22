#ifndef MOLE_H
#define MOLE_H
class DisplayInterface; // forward declaration of DisplayInterface class
class GameLogic;        // forward declaration of GameLogic class

class Mole
{
private:
    int ID;                    // unique identifier for each mole
    int HP;                    // Health Points for each mole
    bool isAlive;              // state of the mole: true if alive, false if not
    bool timeIsUp;             // check if mole's internal timer is up
    bool isHp0;                // check if mole's HP is 0
    unsigned long startime;    // time when the mole came up
    unsigned long currenttime; // current time
    unsigned long duration;    // duration for which the mole stays up
    unsigned long lastDownTime;

public:
    // implemented:
    void setLastDownTime(unsigned long time);
    unsigned long getLastDownTime() const;
    Mole(int ID);                                                      // constructor to initialize mole with ID
    void setHP(int hp);                                                // set HP of mole
    int getHP() const;                                                 // get HP of mole
    void handleDeath(GameLogic *game);                                 // handles mole death (when HP == 0)
    void setPosition(bool up, DisplayInterface *p_di);                 // set position of mole
    bool getPosition() const;                                          // get position of mole
    void handleTimeIsUp(GameLogic *game);                              // handles when mole's internal timer is up
    bool getTimeIsUp() const;                                          // get timeIsUp status
    void decreaseHp(int delta_to_decrease_by, DisplayInterface *p_di); // decrease HP by a certain amount
    void getCurrentTime();                                             // updates currenttime with millis()
    void setStartTime(unsigned long time);                             // sets startime to time when mole comes
    void setDuration(unsigned long dur);                               // sets duration for which mole stays up
    void checkIfTimeIsUp();                                            // checks if currenttime - startime >= duration
};
#endif // MOLE_H