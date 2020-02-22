#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

class Computer : public Player{
public:
    explicit Computer(int playerNumber);
    ~Computer() override;

    PlayerChoice getPlayerChoice() override;

private:

};

#endif