#include "led_interface.h"
#include <iostream>
using namespace std;

void DisplayInterface::show_score(int current_score)
{

    // cout << "Displaying current score: " << current_score << endl;
    // Code to interface with the actual LED hardware would go here
}

void DisplayInterface::startMole(int ID, int maxHP, unsigned long duration)
{
    // cout << "Starting mole with ID: " << ID << ", Max HP: " << maxHP << ", Duration: " << duration << " ms" << endl;
    // Code to interface with the actual LED hardware would go here
}

void DisplayInterface::changeMoleHP(int moleID, int newHP, int maxHP)
{
    // std::cout << "[LED] changeMoleHP id=" << moleID
    //           << " hp=" << newHP << "/" << maxHP << "\n";
}

void DisplayInterface::changeDuration(int moleID, int newDuration)
{
    // std::cout << "[LED] changeDuration id=" << moleID
    //           << " dur=" << newDuration << "ms\n";
}

void DisplayInterface::endMole(int moleID, bool isTimeout, bool isHPZero)
{
    // std::cout << "[LED] endMole id=" << moleID
    //           << " timeout=" << isTimeout
    //           << " hp0=" << isHPZero << "\n";
}

void DisplayInterface::changeMoleColourMode(int moleID, int newColour)
{
    // std::cout << "[LED] changeMoleColourMode id=" << moleID
    //           << " colour=" << newColour << "\n";
}

unsigned long DisplayInterface::update_time(unsigned long time)
{
    // std::cout << "[LED] update_time " << time << "\n";
    return time;
}

void DisplayInterface::update_heart(int lives)
{
    // std::cout << "[LED] update_heart lives=" << lives << "\n";
}
