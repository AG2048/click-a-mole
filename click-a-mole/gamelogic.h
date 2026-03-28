#include "mole.h"
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#define TOTAL_MOLES 1 // CHANGE: TOTAL_MOLES 3

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
class MoleController;   // forward declaration of MoleController class
class GameLogic
{
private:
    Mole **moleArr = nullptr;    // array of mole pointers. NOTE: nullptr is used to ensure that we aren't removing
                                 // memory that hasn't been allocated yet
    int buttonStates[8];         // array of button states from mole modules]
    int score;                   // player's score
    int lives;                   // player's lives
    unsigned long roundDuration; // duration for each round
    int roundMaxMoles;           // maximum number of moles that will come up in a round
    int maxMolesUp;              // maximum number of moles that can be up at once
    int currNumMolesUp;          // number of moles up at the same time
    int numMolesDownThisRound;   // number of moles that have gone down this round
    int moles_interface[8];      // represents the state of each mole in the interface
    int level;
    unsigned long lastSpawnTime;
    unsigned long nextSpawnDelay;
    unsigned long startRound;
    GameState currentGameState;
    GameState nextGameState;
    DisplayInterface *p_di;
    MoleController *p_mi;
    unsigned long freezeUntil;  // millis() timestamp when the freeze effect expires
    unsigned long lastTickTime; // timestamp of the previous fsm() tick, to check if still frozen
public:
    void handleInput(char c);                                // process user input character
    GameLogic(DisplayInterface *p_di, MoleController *p_mi); // constructor to initialize game with number of moles and initial lives
    bool gameEnded();                                        // check if game has ended
    ~GameLogic();                                            // destructor to free dynamically allocated memory
    bool roundEnded() const;                                 // check if round has ended
    void fsm();                                              // main game loop finite state machine
    int getScore() const;
    int getLives() const;
    DisplayInterface *getDisplayInterface() const;
    void setScore(int s);
    void setLives(int l);
    Mole **getMoleArr() const;
    void setFreezeUntil(unsigned long t); // both this and the get function handle the freezing logic
    unsigned long getFreezeUntil() const;
};
#endif // GAMELOGIC_H