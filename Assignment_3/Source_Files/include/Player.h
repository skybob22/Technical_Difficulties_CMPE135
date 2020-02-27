#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerChoice.h"

class Player{
public:
    virtual ~Player();

    int getPlayerNumber() const;
    virtual PlayerChoice::Choice getPlayerChoice() = 0;

    enum PlayerType{
        Human,
        Computer
    };
    static Player* createPlayer(PlayerType type,int playerNumber);

protected:
    explicit Player(int playerNumber);

private:
    int playerNumber;
};

#endif