#include "led_interface.h"
#include <Arduino.h>

void DisplayInterface::show_score(int current_score)
{

    // Serial.print("Displaying current score: ");
    // Serial.println(current_score);
    // Code to interface with the actual LED hardware would go here
}

void DisplayInterface::startMole(int ID, int maxHP, unsigned long duration)
{
    Serial.print("Starting mole with ID: ");
    Serial.print(ID);
    Serial.print(", Max HP: ");
    Serial.print(maxHP);
    Serial.print(", Duration: ");
    Serial.print(duration);
    Serial.println(" ms");
    // Code to interface with the actual LED hardware would go here
}

void DisplayInterface::changeMoleHP(int moleID, int newHP, int maxHP)
{
    Serial.print("[LED] changeMoleHP id=");
    Serial.print(moleID);
    Serial.print(" hp=");
    Serial.print(newHP);
    Serial.print("/");
    Serial.println(maxHP);
}

void DisplayInterface::changeDuration(int moleID, int newDuration)
{
    Serial.print("[LED] changeDuration id=");
    Serial.print(moleID);
    Serial.print(" dur=");
    Serial.print(newDuration);
    Serial.println("ms");
}

void DisplayInterface::endMole(int moleID, bool isTimeout, bool isHPZero)
{
    Serial.print("[LED] endMole id=");
    Serial.print(moleID);
    Serial.print(" timeout=");
    Serial.print(isTimeout);
    Serial.print(" hp0=");
    Serial.println(isHPZero);
}

void DisplayInterface::changeMoleColourMode(int moleID, int newColour)
{
    Serial.print("[LED] changeMoleColourMode id=");
    Serial.print(moleID);
    Serial.print(" colour=");
    Serial.println(newColour);
}

unsigned long DisplayInterface::update_time(unsigned long time)
{
    Serial.print("[LED] update_time ");
    Serial.println(time);
    return time;
}

void DisplayInterface::update_heart(int lives)
{
    Serial.print("[LED] update_heart lives=");
    Serial.println(lives);
}