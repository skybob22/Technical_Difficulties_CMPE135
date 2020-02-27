#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Game.h"
#include <vector>
#include <ostream>

class GameManager{
public:
    GameManager();
    ~GameManager();

    void setNumRounds(unsigned int numRounds);
    void startGame(Game::GameMode gameMode);
    std::vector<Game::GameResult> getMatchHistory() const;

    friend std::ostream& operator<<(std::ostream& stream,const GameManager& gameManager);

private:
    Game* game;
    std::vector<Game::GameResult> matchHistory;
    unsigned int numRounds;
};

#endif