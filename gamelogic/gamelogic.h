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
    int roundMaxMoles;           // maximum number of moles that can be up in a round
    unsigned long roundDuration; // duration for each round
    bool isGameEnded;            // status to check if game has ended
    DisplayInterface *p_di;
    MotorInterface *p_mi;

public:
    GameLogic(DisplayInterface *p_di, MotorInterface *p_mi, int maxNumMoles, int initialLives); // constructor to initialize game with number of moles and initial lives
    int getScore() const;                                                                       // get player's score
    void setScore(int s);                                                                       // set player's score
    int getLives() const;                                                                       // get player's lives
    void setLives(int l);                                                                       // set player's lives
    bool gameEnded();                                                                           // check if game has ended                                                            // set gameEnded status
    Mole **getMoleArr() const;                                                                  // get the array of moles
    ~GameLogic();                                                                               // destructor to free dynamically allocated memor                                                                      // handles end of game when lives reach 0
    bool roundEnded(int molesDownThisRound) const;                                              // check if round has ended
    DisplayInterface *getDisplayInterface() const;                                              // get pointer to DisplayInterface                                             // get pointer to MotorInterface
    void setMaxMolesPerRound(int numMolesThisRound);
    void fsm(); // main game loop finite state machine
};
#endif // GAMELOGIC_H