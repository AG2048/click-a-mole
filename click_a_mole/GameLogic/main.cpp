#include "led_interface.h"
#include "motor_interface.h"
#include "gamelogic.h"
#include "arduino.h"
#include "mole.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// C function showing how to do time delay
#include <stdio.h>
// To use time library of C
#include <time.h>

void delay(int milli_seconds)
{

    // Storing start time
    clock_t start_time = clock();

    // Convert milliseconds to clock ticks (CLOCKS_PER_SEC ticks per second)
    clock_t wait_ticks = (clock_t)milli_seconds * (clock_t)CLOCKS_PER_SEC / 1000;

    // looping till required time is not achieved
    while (clock() < start_time + wait_ticks)
        ;
}

void handleInput(char c, GameLogic &game)
{
    // process user input character (for testing we're using keyboard keys)
    // will map corresponding keys to arduino pins
    cout << "Handling input: " << c << endl;
    // Add input handling logic here
    switch (c)
    {
    case 'q':
        cout << "Escape key pressed. Exiting game." << endl;
        break;
    case '1':
        game.getMoleArr()[0]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 0 hit!" << endl;
        break;
    case '2':
        game.getMoleArr()[1]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 1 hit!" << endl;
        break;
    case '3':
        game.getMoleArr()[2]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 2 hit!" << endl;
        break;
    case '4':
        game.getMoleArr()[3]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 3 hit!" << endl;
        break;
    case '5':
        game.getMoleArr()[4]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 4 hit!" << endl;
        break;
    case '6':
        game.getMoleArr()[5]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 5 hit!" << endl;
        break;
    case '7':
        game.getMoleArr()[6]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 6 hit!" << endl;
        break;
    case '8':
        game.getMoleArr()[7]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 7 hit!" << endl;
        break;
    case '9':
        game.getMoleArr()[8]->decreaseHp(1, game.getDisplayInterface());
        cout << "Mole 8 hit!" << endl;
        break;
    default:
        cout << "Unhandled key pressed: " << c << endl;
        break;
    }
}

int main()
{

    // maxNumMoles and initial lives could be macros for the MMVP
    // but we may need to change them for the Click-A-Mole

    // Game Initialization
    // move to GameLogic
    const int initialLives = 3;    // set to 3 but can update as difficulty increases

    const int initialHP = 2;       // initial player lives
    int maxNumMolesUp = 2;         // maximum number of moles that can be up at once (adjust with difficulty level)
    int numMolesThisRound = 10;    // total number of moles that will come up in a round
    int molesTimer = 5000;         // time (in ms) each mole stays up

    int currNumMolesUp = 0;        // number of moles up at the same time
    int numMolesDownThisRound = 0; // number of moles that have gone down this round

    int moles_interface[9] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    DisplayInterface *p_di = new DisplayInterface;
    MotorInterface *m_di = new MotorInterface;
    {
    GameLogic game(p_di, m_di, maxNumMolesUp, initialLives, initialHP); // create GameLogic object
    // NOTE: We are creating the GameLogic object within a scope to ensure proper destruction at the end of the game.
    game.setMaxMolesPerRound(numMolesThisRound);

//     while (!game.gameEnded())
// { // Game Loop
    cout << "Starting new round." << endl;
    currNumMolesUp = 0;
    numMolesDownThisRound = 0;
    unsigned long start = millis();
    unsigned startRound = millis();

    // Start of Round
    while (!game.roundEnded(numMolesDownThisRound))
    {                                                            // Round Loop
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "Round Time: " << int((millis() - startRound) / 1000) << " seconds" << endl;
        cout << "Mole Timer: 5 seconds each" << endl;
       
        game.getDisplayInterface()->show_score(game.getScore()); // update score display
        int random = rand() % 9;                                 // random number between 0 and 8

        if (millis() - start >= 1000 && game.getMoleArr()[random]->getPosition() == false && currNumMolesUp < maxNumMolesUp)
        {
            start = millis();
            game.getMoleArr()[random]->setPosition(true, game.getDisplayInterface()); // make random mole come up
            game.getMoleArr()[random]->setHP(initialHP);
            game.getMoleArr()[random]->setStartTime(millis());
            currNumMolesUp++;
        }
        char c = game.getInput(); // get user input to whack moles
        handleInput(c, game);

        for (int i = 0; i < 9; i++)
        {
            if (game.getMoleArr()[i]->getPosition() == true){
                game.getMoleArr()[i]->getCurrentTime(); // update current time of mole
                game.getMoleArr()[i]->checkIfTimeIsUp(); // check if mole's time is up
            
            if (game.getMoleArr()[i]->getTimeIsUp())
            {
                game.getMoleArr()[i]->handleTimeIsUp(game); // check if any mole's time is up
                currNumMolesUp--;
                numMolesDownThisRound++;
                if (game.gameEnded())
                {
                    break; // exit for loop if game has ended
                }
            }
            else if (game.getMoleArr()[i]->getHP() == 0)
            {
                game.getMoleArr()[i]->handleDeath(game); // check if any mole has died
                currNumMolesUp--;
                numMolesDownThisRound++;
            }
        }   

            if (game.getMoleArr()[i]->getPosition() == true)
            {
                moles_interface[i] = game.getMoleArr()[i]->getHP(); 
            }
            else {
                moles_interface[i] = '\0'; // Mole is Down
            }

        }

        if (game.gameEnded())
            {
                break; // exit for loop if game has ended
            }
        cout << "----------------------------" << endl;
        cout << "Moles Interface State:" << endl;
        cout << "[" << moles_interface[0] << "][" << moles_interface[1] << "][" << moles_interface[2] << "]" << endl;
        cout << "[" << moles_interface[3] << "][" << moles_interface[4] << "][" << moles_interface[5] << "]" << endl;
        cout << "[" << moles_interface[6] << "][" << moles_interface[7] << "][" << moles_interface[8] << "]" << endl;
        cout << "Number of Lives: " << game.getLives() << endl;
        cout << "Number of Moles Left: " << (numMolesThisRound - numMolesDownThisRound) << endl;
        cout << "\n\n" << endl;
        delay(50);
    }
//  }
    // How did the game end? By win or loss?
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Game has ended. Final score: " << game.getScore() << endl;
    cout << "\n\n" << endl;

    }

    return 0;
}