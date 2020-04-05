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

    static std::string diffToString(Difficulty val);
    static Difficulty stringToDiff(std::string val);

protected:
    static PlayerChoice::Choice getRandomChoice(); //Used by multiple sub-classes

private:
    static const std::unordered_map<Difficulty,std::string> DIFF_TO_STRING_MAP;
    static const std::unordered_map<std::string,Difficulty> STRING_TO_DIFF_MAP;
};

#endif