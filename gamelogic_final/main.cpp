#include <iostream>
#include "gamelogic.h"
#include "arduino.h"
#include "led_interface.h"
#include "motor_interface.h"
using namespace std;
int main()
{
    DisplayInterface *p_di = new DisplayInterface; // Placeholder, replace with actual DisplayInterface object
    MotorInterface *p_mi = new MotorInterface;   // Placeholder, replace with actual MotorInterface
    GameLogic *game = new GameLogic(p_di, p_mi);
    while (true)
    {
        game->fsm();
    }
    return 0;
}
