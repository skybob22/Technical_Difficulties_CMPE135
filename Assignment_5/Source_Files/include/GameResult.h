#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include "PlayerChoice.h"
#include <ostream>

struct GameResult{
public:
    //Data
    std::vector<PlayerChoice::Choice> playerChoices;
    int winner;

    GameResult();
    ~GameResult();

    friend std::ostream& operator<<(std::ostream& stream,GameResult result);
};

#endif