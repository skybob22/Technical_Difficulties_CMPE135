#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Game.h"
#include "GameResult.h"
#include <vector>
#include <ostream>
#include "MainWindow.h"

class MainWindow; //Forward declaration

class GameManager{
public:
    GameManager();
    ~GameManager();

    void setNumRounds(unsigned int numRounds);
    unsigned int getNumRounds();
    unsigned int getRound();
    void startGame(Game::GameMode gameMode);
    void endGame();
    std::vector<GameResult> getMatchHistory() const;

    friend std::ostream& operator<<(std::ostream& stream,const GameManager& gameManager);

private:
    Game* game;
    std::vector<GameResult> matchHistory;
    unsigned int numRounds;
    bool gameStarted;

    friend class MainWindow;
};

#endif