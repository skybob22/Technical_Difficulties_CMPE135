#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GameResult.h"
#include "PlayerChoice.h"
#include <vector>
#include <ostream>
#include "MainWindow.h"

class MainWindow; //Forward Declaration

class Game{
public:
    explicit Game(ComputerDifficulty::Difficulty);
    ~Game();

    void playGame();
    void setPlayerType(unsigned int playerNumber,Player::PlayerType type,ComputerDifficulty::Difficulty diff=ComputerDifficulty::Difficulty::Hard);
    GameResult getResult() const;

private:
    int gameEval(std::vector<PlayerChoice::Choice> choices);

    std::vector<Player*> players;
    GameResult result;

    friend class MainWindow;
};

#endif