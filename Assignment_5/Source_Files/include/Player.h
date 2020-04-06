#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerChoice.h"
#include "GameResult.h"
#include "Difficulty.h"

class Player{
public:
    virtual ~Player();

    int getPlayerNumber() const;
    virtual PlayerChoice::Choice getPlayerChoice() = 0;
    virtual void notifyPlayer(GameResult result);

    enum PlayerType{
        Human,
        Computer
    };
    static Player* createPlayer(PlayerType type,int playerNumber,ComputerDifficulty::Difficulty diff = ComputerDifficulty::Difficulty::Hard);

    static std::string typeToString(PlayerType val);
    static PlayerType stringToType(std::string val);

protected:
    explicit Player(int playerNumber);

private:
    int playerNumber;

    static const std::unordered_map<PlayerType,std::string> TYPE_TO_STRING_MAP;
    static const std::unordered_map<std::string,PlayerType> STRING_TO_TYPE_MAP;
};

#endif