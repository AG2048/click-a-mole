#include "gamelogic.h"
#include "led_interface.h"
#include "motor_interface.h"
using namespace std;
DisplayInterface *p_di = nullptr;
MotorInterface *p_mi = nullptr;
GameLogic *game = nullptr;
setup()
{
    Serial.begin(9600);
    p_di = new DisplayInterface; // Placeholder, replace with actual DisplayInterface object
    p_mi = new MotorInterface;   // Placeholder, replace with actual MotorInterface
    game = new GameLogic(p_di, p_mi);
}
loop()
{
    game->fsm();
}
