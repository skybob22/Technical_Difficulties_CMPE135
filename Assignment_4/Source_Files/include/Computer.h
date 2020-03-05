#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

class Computer : public Player{
public:
    explicit Computer(int playerNumber);
    ~Computer() override;

    enum Difficulty{
        Easy,
        Hard
    };
    static Computer* createComputer(Difficulty diff,int playerNum);

protected:
    static PlayerChoice::Choice getRandomChoice(); //Used by multiple sub-classes
};

#endif