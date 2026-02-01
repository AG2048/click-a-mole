#include "mole.h"
#include "gamelogic.h"
#include "led_interface.h"
#include "MoleController.h"
#include "difficulty.h"
#include <Arduino.h>
#include <stdlib.h>   // for rand() and srand()
#define TOTAL_MOLES 8 // CHANGE: TOTAL_MOLES 3
#define MAX_LIVES 3

char getInput()
{

    if (Serial.available() > 0)
    {                         // if a key is pressed
        return Serial.read(); // return that key
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

void GameLogic::handleInput(char c)
{
    // process user input character (for testing we're using keyboard keys)
    // will map corresponding keys to arduino pins
    // Serial.print("Handling input: ");
    // Serial.println(c);
    // Add input handling logic here
    switch (c)
    {
    case 'q':
        // Serial.println("Escape key pressed. Exiting game.");
        break;
    case '1':
        moleArr[0]->decreaseHp(1, p_di, p_mi);
        Serial.println("Mole 0 hit!");
        break;
    case '2':
        moleArr[1]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 1 hit!");
        break;
    case '3':
        moleArr[2]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 2 hit!");
        break;
    case '4':
        moleArr[3]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 3 hit!");
        break;
    case '5':
        moleArr[4]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 4 hit!");
        break;
    case '6':
        moleArr[5]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 5 hit!");
        break;
    case '7':
        moleArr[6]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 6 hit!");
        break;
    case '8':
        moleArr[7]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 7 hit!");
        break;
    case '9':
        moleArr[8]->decreaseHp(1, p_di, p_mi);
        // Serial.println("Mole 8 hit!");
        break;
    default:
        // Serial.println("Unhandled key pressed: " + String(c));
        break;
    }
}

GameLogic::~GameLogic()
{
    // destructor to free dynamically allocated memory for moleArr
    // iterates through the array and deletes each Mole object, then deletes the array itself
    for (int i = 0; i < TOTAL_MOLES; i++)
    {
        if (moleArr[i] != nullptr)
        {
            delete moleArr[i];
            moleArr[i] = nullptr;
        }
    }
    delete[] moleArr;
    // // Serial.print("Game destructor called. Dynamically allocated memory for moleArr freed.");
}
int GameLogic::getScore() const
{
    // expected output: prints and returns the current score of the player
    // // Serial.print("Current score is" + String(score));
    return score;
}
int GameLogic::getLives() const
{
    // expected output: prints and returns the current number of lives of the player
    // // Serial.print("Current lives are " + String(lives));
    return lives;
}
bool GameLogic::roundEnded() const
{
    // check if round has ended based on number of moles down this round
    return (numMolesDownThisRound >= roundMaxMoles); // Change Back
}

bool GameLogic::gameEnded()
{
    // expected output: prints and returns the current gameEnded status
    return (lives <= 0);
}

GameLogic::GameLogic(DisplayInterface *p_di, MoleController *p_mi)
{
    currentGameState = S_IDLE;
    nextGameState = S_IDLE;
    // make sure to free any existing memory before allocating new memory for moleArr
    // if (moleArr != nullptr)
    // {
    //     for (int i = 0; i < TOTAL_MOLES; i++)
    //     {
    //         if (moleArr[i] != nullptr)
    //         {
    //             delete moleArr[i];
    //             moleArr[i] = nullptr;
    //         }
    //     }
    //     delete[] moleArr; // free existing memory if any
    // }
    // constructor to initialize game with number of moles and initial lives
    // dynamically allocates memory for moleArr and initializes each Mole object
    moleArr = new Mole *[TOTAL_MOLES]; // dynamically allocating array of pointers to Mole objects
    for (int i = 0; i < TOTAL_MOLES; i++)
    {
        moleArr[i] = new Black(i);            // dynamically allocating each Mole object
        moleArr[i]->setPosition(false, p_di); // setting all moles to down position initially
    }
    score = 0;         // initializing score to 0
    lives = MAX_LIVES; // set to 3 but can update as difficulty increases
    // Serial.print(F("Game initialized with"));
    // Serial.print(F(roundMaxMoles));
    // Serial.print(F(" moles and " + String(lives) + " lives."));
    this->p_di = p_di;
    this->p_mi = p_mi;
    maxMolesUp = 1;            // default value, can be changed later
    roundMaxMoles = 10;        // default value, can be changed later
    currNumMolesUp = 0;        // number of moles up at the same time
    numMolesDownThisRound = 0; // number of moles that have gone down this round
    level = 1;
    lastSpawnTime = 0;
    nextSpawnDelay = 0;
    startRound = 0;
}

DisplayInterface *GameLogic::getDisplayInterface() const
{
    // expected output: returns pointer to DisplayInterface
    // // Serial.print("Returning pointer to Display interface");
    return p_di;
}

void GameLogic::setScore(int s)
{
    // takes new score as argument and sets the player's score to that value
    // expected output: player's score is set to the new value
    score = s;
    // // Serial.print("Player's score set to " + String(score));
}

void GameLogic::setLives(int l)
{
    // takes new lives as argument and sets the player's lives to that value
    // expected output: player's lives are set to the new value
    lives = l;
    // // Serial.print("Player's lives set to " + String(lives));
}

Mole **GameLogic::getMoleArr() const
{
    // expected output: returns the array of moles
    // // Serial.print("Returning array of moles.");
    return moleArr;
}

void GameLogic::fsm()
{
    if (currentGameState == S_IDLE)
    {
        // implement a start button
        // Serial.println("Game is in IDLE state. Waiting to start...");
        // Serial.println("Press 's' to start the game.");
        char c = getInput();
        if (c == 's')
        {
            // srand(millis()); // seed random number generator
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
        for (int i = 0; i < TOTAL_MOLES; i++)
        {
            moles_interface[i] = '0';
        }
        Serial.print(F("Game initialized. Starting first round."));
        nextGameState = S_INITIALIZE_ROUND;
    }
    else if (currentGameState == S_INITIALIZE_ROUND)
    {
        // // Serial.print("Starting new round.");
        currNumMolesUp = 0;
        maxMolesUp = maxMolesUpForLevel(level);
        roundMaxMoles = molesPerLevel(level);

        // spawn timing
        lastSpawnTime = millis();
        nextSpawnDelay = randomSpawnDelayForLevel(level);

        startRound = millis();
        nextGameState = S_PLAYING;
    }
    else if (currentGameState == S_PLAYING)
    {
        // // Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        // // Serial.print("Round Time: " + String(int((millis() - startRound) / 1000)) + " seconds");
        // // Serial.print("Mole lifetime ≈ " + String(minDurationForLevel(level) / 1000.0) + "-" + String(maxDurationForLevel(level) / 1000.0) + " seconds");
        p_mi->updateAll();

        p_mi->readButtons(buttonStates);
        p_di->show_score(score); // update score display

        

        unsigned long now = millis();
        int idx = rand() % 8;
        Mole *m = moleArr[idx];
        // try to spawn a new mole if:
        // 1. enough time passed since last spawn
        // 2. we have capacity (currNumMolesUp < maxNumMolesUp)
        // 3. this hole is down
        // 4. this hole respected its per-mole cooldown
        if (now - lastSpawnTime >= nextSpawnDelay &&
            currNumMolesUp < maxMolesUp &&
            m->getPosition() == false &&
            now - m->getLastDownTime() >= MOLE_RESPAWN_COOLDOWN_MS)
        {
            delete m;                   // free existing mole
            int spawnType = rand() % 1; // CHANGE: rand() % 2
            if (spawnType == 0)
            {
                m = new Black(0);
            }
            else
            {
                m = new White(0);
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
            m->setMaxHP(hp);
            m->setHP(hp);
            p_mi->setHp(0, hp, hp);
            m->setPosition(true, p_di); // set mole to up position
            currNumMolesUp++;
            lastSpawnTime = now;
            nextSpawnDelay = randomSpawnDelayForLevel(level);
        }
        char c = getInput(); // get user input to whack moles
        if (c == 'q')
        {
            nextGameState = S_IDLE;
        }
        else if (c >= '1' && c < '1' + TOTAL_MOLES)
        {
            buttonStates[c - '1'] = 1; // mark button as pressed
        }

        for (int i = 0; i < TOTAL_MOLES; i++)
        {
            if (buttonStates[i] == 1)
            {
                handleInput('1' + i); // map button press to corresponding mole hit
                buttonStates[i] = 0;
            }
            Serial.println(moleArr[i]->getHP());
            Serial.println(moleArr[i]->maxHP);
        }

        p_mi->readButtons(buttonStates); // read button states again after handling input

        for (int i = 0; i < TOTAL_MOLES; i++)
        {
            bool oldPosition = moleArr[i]->getPosition();
            moleArr[i]->update(this); // update all moles
            bool newPosition = moleArr[i]->getPosition();
            if (oldPosition == true && newPosition == false)
            {
                // Mole just went down
                currNumMolesUp--;
                numMolesDownThisRound++;
            }
            if (newPosition == true)
            {
                moles_interface[i] = moleArr[i]->getHP();
            }
            else
            {
                moles_interface[i] = '\0'; // Mole is Down
            }
        }
    //     Serial.println(F("----------------------------"));
    // Serial.println(F("Moles Interface State:"));

    // // Row 1
    Serial.print(F("[")); Serial.print(moles_interface[0]); Serial.print(F("]"));
    Serial.print(F("[")); Serial.print(moles_interface[1]); Serial.print(F("]"));
    Serial.print(F("[")); Serial.print(moles_interface[2]); Serial.println(F("]"));

    // // // Row 2
    Serial.print(F("[")); Serial.print(moles_interface[3]); Serial.print(F("]"));
    Serial.print(F("[")); Serial.print(moles_interface[4]); Serial.print(F("]"));
    Serial.print(F("[")); Serial.print(moles_interface[5]); Serial.println(F("]"));

    // // // Row 3
    Serial.print(F("[")); Serial.print(moles_interface[6]); Serial.print(F("]"));
    Serial.print(F("[")); Serial.print(moles_interface[7]); Serial.print(F("]"));

    // Status Info
    Serial.print(F("Number of Lives: "));
    Serial.println(lives);

    Serial.print(F("Number of Moles Left: "));
    Serial.println(roundMaxMoles - numMolesDownThisRound);
    Serial.println(); // Extra newline for spacing

        if (gameEnded())
        {
            nextGameState = S_GAMEOVER;
        }
        else if (roundEnded())
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
        p_mi->resetHp(); // TO DO + loop over moles to reset hp and position
        // Handle game over state
        // print game over
        // Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        // Serial.print("Game has ended. Final score: " + String(score));
        // Serial.print("\n\n"

        // delay to simulate display time
        nextGameState = S_IDLE;
    }
    else if (currentGameState == S_LEADERBOARD)
    {
        // Handle leaderboard state
        // string input;
        // while (input.length() == 0)
        // {
        //     // Serial.print("Enter your name for the leaderboard: ");
        //     getline(cin, input);
        //     stringstream line(input);
        // }

        // // display line on the leaderboard
        // // Serial.print("Thank you for playing, " + String(input.c_str()) + "!");
        nextGameState = S_IDLE;
    }
    else
    {
        // Serial.print("Unknown game state!");
    }
    currentGameState = nextGameState;
}
