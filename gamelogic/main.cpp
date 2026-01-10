#include "led_interface.h"
#include "motor_interface.h"
#include "gamelogic.h"
#include "arduino.h"
#include "mole.h"
#include <iostream>
#include <cstdlib>
#include "difficulty.h"
#include <sstream>
#include <string>
#include <conio.h> // for _kbhit() and _getch()
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

void handleInput(char c, GameLogic *game)
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
        game->getMoleArr()[0]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 0 hit!" << endl;
        break;
    case '2':
        game->getMoleArr()[1]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 1 hit!" << endl;
        break;
    case '3':
        game->getMoleArr()[2]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 2 hit!" << endl;
        break;
    case '4':
        game->getMoleArr()[3]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 3 hit!" << endl;
        break;
    case '5':
        game->getMoleArr()[4]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 4 hit!" << endl;
        break;
    case '6':
        game->getMoleArr()[5]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 5 hit!" << endl;
        break;
    case '7':
        game->getMoleArr()[6]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 6 hit!" << endl;
        break;
    case '8':
        game->getMoleArr()[7]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 7 hit!" << endl;
        break;
    case '9':
        game->getMoleArr()[8]->decreaseHp(1, game->getDisplayInterface());
        cout << "Mole 8 hit!" << endl;
        break;
    default:
        cout << "Unhandled key pressed: " << c << endl;
        break;
    }
}

char getInput()
{

    if (_kbhit())
    {                    // if a key is pressed
        return _getch(); // return that key
    }
    else
    {
        return '\0'; // default: no key pressed
    }

    /*
    if (kbhit() > 0)
    { // usually just written as `if( kbhit() )`
        int input_int = getchar();
        char input = (char)input_int;
        if (input_int == EOF)
        {
            // Handle the EOF case, perhaps by returning a sentinel value
            input = '\0'; // or some other appropriate value
        }

        inputs += input;
        return input;
    }
    else
    {
        return '\0';
    }

    */
}

GameState currentGameState = S_IDLE;
GameState nextGameState = S_IDLE;

const int initialLives = 3;    // set to 3 but can update as difficulty increases
int currNumMolesUp = 0;        // number of moles up at the same time
int numMolesDownThisRound = 0; // number of moles that have gone down this round
int maxNumMolesUp = 0;         // maximum number of moles that can
int moles_interface[9];        // represents the state of each mole in the interface
int level = 1;
int numMolesThisRound = 0; // total number of moles that will come up in a round
GameLogic *game = NULL;
DisplayInterface *p_di = NULL;
MotorInterface *m_di = NULL;
unsigned long lastSpawnTime = 0;
unsigned long nextSpawnDelay = 0;
unsigned long startRound = 0;

int main()
{
    bool running = true;
    while (running)
    {
        // opt for verbose output on arduino IDE
        if (currentGameState == S_IDLE)
        {
            // implement a start button
            cout << "Game is in IDLE state. Waiting to start..." << endl;
            cout << "Press 's' to start the game." << endl;
            char c = getInput();
            if (c == 's')
            {
                srand(millis()); // seed random number generator
                nextGameState = S_INITIALIZE_GAME;
            }
            else
            {
                nextGameState = S_IDLE;
            }
            // p->di idle display animation
        }
        else if (currentGameState == S_INITIALIZE_GAME)
        {

            maxNumMolesUp = 2;      // maximum number of moles that can be up at once (adjust with difficulty level)
            numMolesThisRound = 10; // total number of moles that will come up in a round

            currNumMolesUp = 0;        // number of moles up at the same time
            numMolesDownThisRound = 0; // number of moles that have gone down this round
            for (int i = 0; i < 9; i++)
            {
                moles_interface[i] = '\0';
            }
            if (!p_di)
                p_di = new DisplayInterface;
            if (!m_di)
                m_di = new MotorInterface;
            if (!game)
                game = new GameLogic(p_di, m_di, maxNumMolesUp, initialLives);
            cout << "Game initialized. Starting first round." << endl;
            nextGameState = S_INITIALIZE_ROUND;
        }
        else if (currentGameState == S_INITIALIZE_ROUND)
        {
            cout << "Starting new round." << endl;
            currNumMolesUp = 0;
            numMolesDownThisRound = 0;
            maxNumMolesUp = maxMolesUpForLevel(level);
            numMolesThisRound = molesPerLevel(level);
            game->setMaxMolesPerRound(numMolesThisRound);

            // spawn timing
            lastSpawnTime = millis();
            nextSpawnDelay = randomSpawnDelayForLevel(level);

            startRound = millis();
            nextGameState = S_PLAYING;
        }
        else if (currentGameState == S_PLAYING)
        {
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << "Round Time: " << int((millis() - startRound) / 1000) << " seconds" << endl;
            cout << "Mole lifetime ≈ "
                 << minDurationForLevel(level) / 1000.0
                 << "-" << maxDurationForLevel(level) / 1000.0
                 << " seconds" << endl;

            game->getDisplayInterface()->show_score(game->getScore()); // update score display

            unsigned long now = millis();
            int idx = rand() % 9;
            Mole *m = game->getMoleArr()[idx];
            // try to spawn a new mole if:
            // 1. enough time passed since last spawn
            // 2. we have capacity (currNumMolesUp < maxNumMolesUp)
            // 3. this hole is down
            // 4. this hole respected its per-mole cooldown
            if (now - lastSpawnTime >= nextSpawnDelay &&
                currNumMolesUp < maxNumMolesUp &&
                m->getPosition() == false &&
                now - m->getLastDownTime() >= MOLE_RESPAWN_COOLDOWN_MS)
            {
                delete m; // free existing mole
                int spawnType = rand() % 2;
                if (spawnType == 0)
                {
                    m = new Black(idx);
                }
                else
                {
                    m = new White(idx);
                }
                unsigned long minDur = minDurationForLevel(level);
                unsigned long maxDur = maxDurationForLevel(level);
                if (minDur > maxDur)
                {
                    unsigned long tmp = minDur;
                    minDur = maxDur;
                    maxDur = tmp;
                }
                unsigned long lifetime = minDur + (rand() % (int)(maxDur - minDur + 1));

                m->setDuration(lifetime);
                m->setStartTime(now);

                int hp = randomHpForMole(level, lifetime);
                m->setHP(hp);
                m->setPosition(true, game->getDisplayInterface()); // set mole to up position
                currNumMolesUp++;
                lastSpawnTime = now;
                nextSpawnDelay = randomSpawnDelayForLevel(level);
            }
            char c = getInput(); // get user input to whack moles
            if (c == 'q')
            {
                nextGameState = S_IDLE;
            }
            else
            {
                handleInput(c, game);
            }
            for (int i = 0; i < 9; i++)
            {
                bool oldPosition = game->getMoleArr()[i]->getPosition();
                game->getMoleArr()[i]->update(game); // update all moles
                bool newPosition = game->getMoleArr()[i]->getPosition();

                if (oldPosition == true && newPosition == false)
                {
                    // Mole just went down
                    currNumMolesUp--;
                    numMolesDownThisRound++;
                }
                if (newPosition == true)
                {
                    moles_interface[i] = game->getMoleArr()[i]->getHP();
                }
                else
                {
                    moles_interface[i] = '\0'; // Mole is Down
                }
            }
            cout << "----------------------------" << endl;
            cout << "Moles Interface State:" << endl;
            cout << "[" << moles_interface[0] << "][" << moles_interface[1] << "][" << moles_interface[2] << "]" << endl;
            cout << "[" << moles_interface[3] << "][" << moles_interface[4] << "][" << moles_interface[5] << "]" << endl;
            cout << "[" << moles_interface[6] << "][" << moles_interface[7] << "][" << moles_interface[8] << "]" << endl;
            cout << "Number of Lives: " << game->getLives() << endl;
            cout << "Number of Moles Left: " << (numMolesThisRound - numMolesDownThisRound) << endl;
            cout << "\n\n"
                 << endl;
            delay(50);
            if (game->gameEnded())
            {
                nextGameState = S_GAMEOVER;
            }
            else if (game->roundEnded(numMolesDownThisRound))
            {
                nextGameState = S_INBETWEENLEVELS;
            }
            else
            {
                nextGameState = S_PLAYING;
            }
        }
        else if (currentGameState == S_INBETWEENLEVELS)
        {
            // Handle in-between levels state
            level++;
            nextGameState = S_INITIALIZE_ROUND;
        }
        else if (currentGameState == S_GAMEOVER)
        {
            // Handle game over state
            // print game over
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << "Game has ended. Final score: " << game->getScore() << endl;
            cout << "\n\n"
                 << endl;
            // delay to simulate display time
            delete game;
            game = NULL;
            delete p_di;
            p_di = NULL;
            delete m_di;
            m_di = NULL;
            nextGameState = S_IDLE;
        }
        else if (currentGameState == S_LEADERBOARD)
        {
            // Handle leaderboard state
            string input;
            while (input.length() == 0)
            {
                cout << "Enter your name for the leaderboard: " << endl;
                getline(cin, input);
                stringstream line(input);
            }

            // display line on the leaderboard
            cout << "Thank you for playing, " << input << "!" << endl;
            nextGameState = S_IDLE;
        }
        else
        {
            cout << "Unknown game state!" << endl;
            running = false;
        }
        currentGameState = nextGameState;
        delay(100); // small delay to avoid busy looping REMOVE FOR FSM
    }

    return 0;
}
