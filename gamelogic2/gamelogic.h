#include "mole.h"
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

enum GameState
{
    S_IDLE,
    S_INITIALIZE_GAME,
    S_PLAYING,
    S_INITIALIZE_ROUND,
    S_INBETWEENLEVELS, // post-round state
    S_GAMEOVER,
    S_LEADERBOARD
};

class DisplayInterface; // forward declaration of DisplayInterface class
class MotorInterface;   // forward declaration of MotorInterface class
class GameLogic
{
private:
    Mole **moleArr = nullptr;    // array of mole pointers. NOTE: nullptr is used to ensure that we aren't removing
                                 // memory that hasn't been allocated yet
    int score;                   // player's score
    int lives;                   // player's lives
    unsigned long roundDuration; // duration for each round
    int roundMaxMoles;           // maximum number of moles that will come up in a round
    int maxMolesUp;              // maximum number of moles that can be up at once
    int currNumMolesUp;          // number of moles up at the same time
    int numMolesDownThisRound;   // number of moles that have gone down this round
    int moles_interface[9];      // represents the state of each mole in the interface
    int level;
    unsigned long lastSpawnTime;
    unsigned long nextSpawnDelay;
    unsigned long startRound;
    GameState currentGameState;
    GameState nextGameState;
    DisplayInterface *p_di;
    MotorInterface *p_mi;

public:
    void handleInput(char c);                                // process user input character
    GameLogic(DisplayInterface *p_di, MotorInterface *p_mi); // constructor to initialize game with number of moles and initial lives
    bool gameEnded();                                        // check if game has ended
    ~GameLogic();                                            // destructor to free dynamically allocated memory
    bool roundEnded() const;                                 // check if round has ended
    void fsm();                                              // main game loop finite state machine
};
#endif // GAMELOGIC_H