#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Game.h"
#include "GameResult.h"
#include <vector>
#include <ostream>
#include "MainWindow.h"

class MainWindow; //Forward declaration
class Game; //Forward declaration

class GameManager{
public:
    GameManager();
    ~GameManager();

    void setNumRounds(unsigned int numRounds);
    unsigned int getNumRounds();
    unsigned int getRound();

    void startGame(ComputerDifficulty::Difficulty diff);
    void playRound();
    void endGame();
    bool isGameInProgress();

    std::vector<unsigned int> getNumWins();
    unsigned int getWinner();

    std::vector<GameResult> getMatchHistory() const;

private:
    Game* game;
    std::vector<GameResult> matchHistory;
    unsigned int numRounds;
    unsigned int currentRound;

    static const unsigned int DEFAULT_NUM_PLAYERS;

    friend class MainWindow;
};

#endif