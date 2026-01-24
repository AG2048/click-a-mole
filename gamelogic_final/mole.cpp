#include "gamelogic.h"
#include "mole.h"
#include "led_interface.h"

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
    if (HP <= maxHP)
        HP = hp;
    else
        HP = maxHP;
    /* Serial.print("Mole");
    Serial.print(ID);
    Serial.print("Mole ");
    Serial.print(ID);
    Serial.print("'s HP set to ");
    Serial.println(HP); */
}

int Mole::getHP() const
{
    // expected output: returns the current HP of the mole
    // Serial.print("Mole");
    // Serial.print(ID);
    // Serial.print("'s current HP is ");
    // Serial.println(HP);
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
    // Serial.print("Mole ");
    // Serial.print(ID);
    // Serial.print(" position set to ");
    // Serial.println(isAlive ? "up" : "down");
}

bool Mole::getPosition() const
{
    // expected output: prints position and returns true if mole is up (visible), false if down (not visible)
    // Serial.print("Mole ");
    // Serial.print(ID);
    // Serial.print(" position is ");
    // Serial.println(isAlive ? "up" : "down");
    return isAlive;
}

void Mole::handleDeath(GameLogic *game)
{
    // function takes game object as a parameter by reference so it can increment score
    // expected output: mole goes back down (isAlive = false) and player's score increments by 1

    setPosition(false, game->getDisplayInterface());
    // set mole position to down
    game->setScore(game->getScore() + 1);
    // increment player's score by 1
    game->getDisplayInterface()->endMole(ID, false, true); // notify display that mole ended due to HP reaching 0
    // Serial.print("Mole ");
    // Serial.print(ID);
    // Serial.println(" has died. Going back down and incrementing score.");
    lastDownTime = millis();
}

bool Mole::getTimeIsUp() const
{
    // expected output: prints timeIsUp status and returns true if time is up, false otherwise
    // Serial.print("Mole ");
    // Serial.print(ID);
    // Serial.print("'s timeIsUp status is ");
    // Serial.println(timeIsUp ? "true" : "false");
    return timeIsUp;
}

void Mole::handleTimeIsUp(GameLogic *game)
{
    // function takclales game object as a parameter by reference so it can decrement lives
    // expected output: mole goes back down (isAlive = false) and player's lives decrements by 1
    setPosition(false, game->getDisplayInterface()); // set mole position to down
    if (game->getLives() > 0)
        game->setLives(game->getLives() - 1); // decrement player's lives by 1
    else
        game->setLives(0);
    // ensure lives do not go negative
    game->getDisplayInterface()->endMole(ID, true, false); // notify display that mole ended due to timeout
    game->getDisplayInterface()->update_heart(game->getLives());
    timeIsUp = false;
    // Serial.print("Mole ");
    // Serial.print(ID);
    // Serial.println("'s time is up. Going back down and decrementing lives.");
    lastDownTime = millis();
}

// call this only when mole is hit AND RELEASED

void Mole::decreaseHp(int delta_to_decrease_by, DisplayInterface *p_di)
{
    // takes an integer argument to decrease the mole's HP by that amount
    // expected output: mole's HP decreases by the specified amount
    if (isAlive == false)
    {
        // Serial.print("Mole ");
        // Serial.print(ID);
        // Serial.println("is down. Cannot decrease HP.");
        return;
    }
    HP -= delta_to_decrease_by;
    p_di->changeMoleHP(ID, HP, 3); // assuming max HP is 3
    if (HP < 0)
        HP = 0; // Ensure HP doesn't go negative
    // Serial.print("Mole's HP decreased by ");
    // Serial.print(delta_to_decrease_by);
    // Serial.print(". New HP is ");
    // Serial.println(HP);
}

void Mole::setMaxHP(int max_hp)
{
    // sets maximum HP for the mole
    maxHP = max_hp;
}

void Mole::increaseHp(int delta_to_increase_by, DisplayInterface *p_di)
{
    // takes an integer argument to increase the mole's HP by that amount
    // expected output: mole's HP increases by the specified amount
    if (isAlive == false)
    {
        // Serial.print("Mole ");
        // Serial.print(ID);
        // Serial.println("is down. Cannot increase HP.");
        return;
    }
    HP += delta_to_increase_by;
    p_di->changeMoleHP(ID, HP, 3); // assuming max HP is 3
    if (HP >= maxHP)
        HP = maxHP; // Ensure HP doesn't go over max
    // Serial.print("Mole's HP increased by ");
    // Serial.print(delta_to_increase_by);
    // Serial.print(". New HP is ");
    // Serial.println(HP);
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
    Serial.print("Current Time Elapsed for Mole ");
    Serial.print(ID);
    Serial.print(": ");
    Serial.print(int(currenttime - startime)); // in milliseconds cause converstion to seconds is expensive
    Serial.println("ms");
}

void Black::update(GameLogic *game)
{
    getCurrentTime();
    checkIfTimeIsUp();
    if (getTimeIsUp() && getPosition())
    {
        handleTimeIsUp(game);
    }
    else if (HP <= 0 && getPosition())
    {
        handleDeath(game);
    }
}

void White::update(GameLogic *game)
{
    getCurrentTime();
    checkIfTimeIsUp();
    if (getTimeIsUp() && getPosition())
    {
        handleTimeIsUp(game);
    }
    else if (HP <= 0 && getPosition())
    {
        handleDeath(game);
    }
    else
    {
        // WHITE MOLE HEALS ALL OTHER MOLES BY 1 HP EVERY SECOND
        Mole **moles = game->getMoleArr();
        unsigned long now = millis();
        if (now - lastHealTime < 1000)
        {
            return; // only heal after 1 second has passed since coming up
        }
        lastHealTime = now; // reset healtime for next heal interval
        for (int i = 0; i < 9; i++)
        {
            // increase HP checks if mole is up
            // if it's up, increases HP by 1
            // if it's at max HP or down, does nothing
            moles[i]->increaseHp(1, game->getDisplayInterface());
        }
    }
}