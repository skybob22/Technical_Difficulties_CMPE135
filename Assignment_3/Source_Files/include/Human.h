#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player{
public:
    explicit Human(int playerNumber);
    ~Human() override;

    PlayerChoice getPlayerChoice() override;

private:

};

#endif