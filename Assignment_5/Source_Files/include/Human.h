#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player{
public:
    explicit Human(int playerNumber);
    ~Human() override;

    void setPlayerChoice(PlayerChoice::Choice choice);
    PlayerChoice::Choice getPlayerChoice() override;

private:
    PlayerChoice::Choice humanChoice;
};

#endif