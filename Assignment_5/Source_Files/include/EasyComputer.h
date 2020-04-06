#ifndef EASY_COMPUTER_H
#define EASY_COMPUTER_H

#include "Computer.h"

class EasyComputer : public Computer{
public:
    explicit EasyComputer(int playerNum);
    ~EasyComputer() override;

    ComputerDifficulty::Difficulty getDifficulty() override;

    PlayerChoice::Choice getPlayerChoice() override;

private:

};

#endif