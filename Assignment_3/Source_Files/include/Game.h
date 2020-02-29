#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GameResult.h"
#include "PlayerChoice.h"
#include <vector>
#include <ostream>

class Game{
public:
    enum GameMode{
        PVP,
        PVE,
        EVE
    };

    explicit Game(GameMode);
    ~Game();

    void playGame();
    GameResult getResult() const;

private:
    int gameEval(std::vector<PlayerChoice::Choice> choices);

    std::vector<Player*> players;
    GameResult result;
};

#endif