#include "gamelogic.h"
#include "led_interface.h"
#include <Arduino.h>
#include "MoleController.h"
#include "MoleModule.h"

DisplayInterface *p_di = nullptr;
MoleController *p_mi = nullptr;
GameLogic *game = nullptr;

void setup()
{
    Serial.begin(9600);
    p_di = new DisplayInterface; 
    p_mi = new MoleController;  
    game = new GameLogic(p_di, p_mi);
    p_mi->init();
    p_di->begin();
    
    p_mi->addModule(
        new MoleModule(
            {22, &PORTA, (1 << PA0)}, // pul
            {23, &PORTA, (1 << PA1)}, // dir
            38,                       // button
            0                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {22, &PORTA, (1 << PA0)}, // pul
            {23, &PORTA, (1 << PA1)}, // dir
            38,                       // button
            0                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {24, &PORTA, (1 << PA2)}, // pul
            {25, &PORTA, (1 << PA3)}, // dir
            39,                       // button
            1                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {26, &PORTA, (1 << PA4)}, // pul
            {27, &PORTA, (1 << PA5)}, // dir
            40,                       // button
            2                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {28, &PORTA, (1 << PA6)}, // pul
            {29, &PORTA, (1 << PA7)}, // dir
            41,                       // button
            3                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {30, &PORTC, (1 << PC7)}, // pul
            {31, &PORTC, (1 << PC6)}, // dir
            42,                       // button
            4                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {32, &PORTC, (1 << PC5)}, // pul
            {33, &PORTC, (1 << PC4)}, // dir
            43,                       // button
            5                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {34, &PORTC, (1 << PC3)}, // pul
            {35, &PORTC, (1 << PC2)}, // dir
            44,                       // button
            6                         // mux channel
            ));

    p_mi->addModule(
        new MoleModule(
            {36, &PORTC, (1 << PC1)}, // pul
            {37, &PORTC, (1 << PC0)}, // dir
            45,                       // button
            7                         // mux channel
            ));

    Serial.println(F("Setup init"));
    // delay(500);

    p_mi->startTimer();
    Serial.println(F("Setup complete"));
}

void loop()
{
    uint32_t gameLoopStartTime = micros();
    game->fsm();
    p_di->process_timed_animations(millis());
    uint32_t gameLoopEndTime = micros();
    // Serial.println(gameLoopEndTime - gameLoopStartTime);
}
