#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include "Difficulty.h"

class Computer : public Player{
public:
    explicit Computer(int playerNumber);
    ~Computer() override;

    static Computer* createComputer(ComputerDifficulty::Difficulty diff,int playerNum);
    virtual ComputerDifficulty::Difficulty getDifficulty() = 0;

protected:
    static PlayerChoice::Choice getRandomChoice(); //Used by multiple sub-classes
};

#endif