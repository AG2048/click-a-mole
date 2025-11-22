#include "gamelogic.h"
#include "mole.h"
#include "arduino.h"
#include <iostream>
#include "led_interface.h"
using namespace std;

void Mole::setLastDownTime(unsigned long time)
{
    lastDownTime = time;
}

unsigned long Mole::getLastDownTime() const
{
    return lastDownTime;
}

void Mole::setHP(int hp)
{
    // takes new hp as argument and sets the mole's HP to that value
    // expected output: mole's HP is set to the new value
    HP = hp;
    // cout << "Mole " << ID << "'s HP set to " << HP << endl;
}

int Mole::getHP() const
{
    // expected output: returns the current HP of the mole
    // cout << "Mole " << ID << "'s current HP is " << HP << endl;
    return HP;
}

void Mole::setPosition(bool alive, DisplayInterface *p_di)
{
    if (alive)
    {
        p_di->startMole(ID, HP, duration); // Should be default colour mode that will be applied
    }
    // takes a boolean argument to set the position of the mole
    // expected output: if up is true, mole is set to up (visible); if false, mole is set to down (not visible)
    isAlive = alive;
    // cout << "Mole " << ID << " position set to " << (isAlive ? "up" : "down") << endl;
}

bool Mole::getPosition() const
{
    // expected output: prints position and returns true if mole is up (visible), false if down (not visible)
    // cout << "Mole " << ID << " position is " << (isAlive ? "up" : "down") << endl;
    return isAlive;
}

void Mole::handleDeath(GameLogic &game)
{
    // function takes game object as a parameter by reference so it can increment score
    // expected output: mole goes back down (isAlive = false) and player's score increments by 1
    HP = game.getInitialHP();
    // set mole's HP to initial HP
    setPosition(false, game.getDisplayInterface());
    // set mole position to down
    game.setScore(game.getScore() + 1);
    // increment player's score by 1
    game.getDisplayInterface()->endMole(ID, false, true); // notify display that mole ended due to HP reaching 0  
    // cout << "Mole " << ID << " has died. Going back down and incrementing score." << endl;
    lastDownTime = millis();
}

bool Mole::getTimeIsUp() const
{
    // expected output: prints timeIsUp status and returns true if time is up, false otherwise
    // cout << "Mole " << ID << "'s timeIsUp status is " << (timeIsUp ? "true" : "false") << endl;
    return timeIsUp;
}

void Mole::handleTimeIsUp(GameLogic &game)
{
    // function takclales game object as a parameter by reference so it can decrement lives
    // expected output: mole goes back down (isAlive = false) and player's lives decrements by 1
    setPosition(false, game.getDisplayInterface()); // set mole position to down
    if (game.getLives() > 0)
        game.setLives(game.getLives() - 1); // decrement player's lives by 1
    else
        game.setLives(0);
    // ensure lives do not go negative
    game.getDisplayInterface()->endMole(ID, true, false); // notify display that mole ended due to timeout
    game.getDisplayInterface()->update_heart(game.getLives());
    timeIsUp = false;
    // cout << "Mole " << ID << "'s time is up. Going back down and decrementing lives." << endl;
    lastDownTime = millis();
}

// call this only when mole is hit AND RELEASED

void Mole::decreaseHp(int delta_to_decrease_by, DisplayInterface *p_di)
{
    // takes an integer argument to decrease the mole's HP by that amount
    // expected output: mole's HP decreases by the specified amount
    if (isAlive == false)
    {
        // cout << "Mole " << ID << "is down. Cannot decrease HP." << endl;
        return;
    }
    HP -= delta_to_decrease_by;
    p_di->changeMoleHP(ID, HP, 3); // assuming max HP is 3
    if (HP < 0)
        HP = 0; // Ensure HP doesn't go negative
    // cout << "Mole's HP decreased by " << delta_to_decrease_by << ". New HP is " << HP << endl;
}

Mole::Mole(int ID)
{
    // default constructor
    this->ID = ID;   // default ID
    HP = 0;          // default HP
    isAlive = false; // default position is down
    timeIsUp = false;
    isHp0 = false;
    startime = 0;
    currenttime = 0;
    duration = 5000; // default duration 5 seconds
    lastDownTime = 0;
}

void Mole::getCurrentTime()
{
    // updates currenttime with millis()
    currenttime = millis();
}

void Mole::setStartTime(unsigned long time)
{
    // sets startime to time when mole comes up
    startime = time;
}

void Mole::setDuration(unsigned long dur)
{
    // sets duration for which mole stays up
    duration = dur;
}

void Mole::checkIfTimeIsUp()
{
    // checks if currenttime - startime >= duration
    if (currenttime - startime >= duration)

    {
        timeIsUp = true;
    }
    cout << "Current Time Elapsed for Mole " << ID << ": " << int(currenttime - startime) / 1000 << " s" << endl;
}