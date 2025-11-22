#include "mole.h"
#include "gamelogic.h"
#include <iostream>
#include "arduino.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // for _kbhit() and _getch()

using namespace std;
GameLogic::~GameLogic()
{
    // destructor to free dynamically allocated memory for moleArr
    // iterates through the array and deletes each Mole object, then deletes the array itself
    for (int i = 0; i < 9; i++)
    {
        if (moleArr[i] != nullptr)
        {
            delete moleArr[i];
            moleArr[i] = nullptr;
        }
    }
    delete[] moleArr;
    // cout << "Game destructor called. Dynamically allocated memory for moleArr freed." << endl;
}
int GameLogic::getScore() const
{
    // expected output: prints and returns the current score of the player
    // cout << "Current score is " << score << endl;
    return score;
}

void GameLogic::setScore(int s)
{
    // takes new score as argument and sets the player's score to that value
    // expected output: player's score is set to the new value
    score = s;
    // cout << "Player's score set to " << score << endl;
}
int GameLogic::getLives() const
{
    // expected output: prints and returns the current number of lives of the player
    // cout << "Current lives are " << lives << endl;
    return lives;
}
void GameLogic::setLives(int l)
{
    // takes new lives as argument and sets the player's lives to that value
    // expected output: player's lives are set to the new value
    lives = l;
    // cout << "Player's lives set to " << lives << endl;
}
bool GameLogic::roundEnded(int numMolesDownThisRound) const
{

    // check if round has ended based on number of moles down this round
    bool roundEnded = false;
    if (numMolesDownThisRound >= roundMaxMoles)
    {
        roundEnded = true;
    }
    return roundEnded; // Change Back
}

bool GameLogic::gameEnded()
{
    // instead of reinitializing the gameEnded variable, we can initialize the variable in constructor and just update it here
    if (lives <= 0)
    {
        isGameEnded = true;
    }

    // expected output: prints and returns the current gameEnded status
    // cout << "Game ended status is " << (isGameEnded ? "true" : "false") << endl;
    return isGameEnded;
}

Mole **GameLogic::getMoleArr() const
{
    // expected output: returns the array of moles
    // cout << "Returning array of moles." << endl;
    return moleArr;
}
void GameLogic::handleGameEnd()
{
    // only runs when gameEnded = true (lives are 0)
    // expected output: prints a message indicating the game has ended and calls Game destructor

    // delete this; // calls destructor to free memory
    // ISSUE: Deleting 'this' is used when initially allocating an object on the heap using 'new'.
    // However, in this case, if the GameLogic object is created on the stack (not using 'new'),
    // deleting 'this' would lead to undefined behavior.

    cout << "Game over! Player's lives have reached 0." << endl;
}
GameLogic::GameLogic(DisplayInterface *p_di, MotorInterface *p_mi, int maxNumMoles, int initialLives)
{
    // make sure to free any existing memory before allocating new memory for moleArr
    if (moleArr != nullptr)
    {
        for (int i = 0; i < 9; i++)
        {
            if (moleArr[i] != nullptr)
            {
                delete moleArr[i];
                moleArr[i] = nullptr;
            }
        }
        delete[] moleArr; // free existing memory if any
    }
    // constructor to initialize game with number of moles and initial lives
    // dynamically allocates memory for moleArr and initializes each Mole object
    moleArr = new Mole *[9]; // dynamically allocating array of pointers to Mole objects
    for (int i = 0; i < 9; i++)
    {
        moleArr[i] = new Mole(i);             // dynamically allocating each Mole object
        moleArr[i]->setPosition(false, p_di); // setting all moles to down position initially
    }
    score = 0;            // initializing score to 0
    lives = initialLives; // setting initial lives
    cout << "Game initialized with " << maxNumMoles << " moles and " << initialLives << " lives." << endl;
    this->p_di = p_di;
    this->p_mi = p_mi;
    roundMaxMoles = maxNumMoles;
    isGameEnded = false;
}

DisplayInterface *GameLogic::getDisplayInterface() const
{
    // expected output: returns pointer to DisplayInterface
    // cout << "Returning pointer to DisplayInterface." << endl;
    return p_di;
}

char GameLogic::getInput()
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

void GameLogic::setMaxMolesPerRound(int maxMoles)
{
    // takes maximum number of moles per round as argument and sets it
    // expected output: maximum number of moles per round is set to the new value
    roundMaxMoles = maxMoles;
    cout << "Maximum number of moles per round set to " << roundMaxMoles << endl;
}
