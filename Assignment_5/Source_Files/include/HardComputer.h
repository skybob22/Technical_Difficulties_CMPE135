#ifndef HARD_COMPUTER_H
#define HARD_COMPUTER_H

#include "Computer.h"
#include "PlayerChoice.h"
#include <unordered_map>
#include <mutex>
#include <deque>
#include <map>

class HardComputer : public Computer{
public:
    explicit HardComputer(int playerNum);
    ~HardComputer() override;

    ComputerDifficulty::Difficulty getDifficulty() override;

    PlayerChoice::Choice getPrediction();
    PlayerChoice::Choice getPlayerChoice() override;
    void notifyPlayer(GameResult result) override;

private:
    void parseFromFile(std::string filename);
    void writeToFile(std::string filename);

    static const std::string FILE_PATH;
    static std::mutex FILE_LOCK;
    static const unsigned int HISTORY_LENGTH;

    std::deque<PlayerChoice::Choice> matchHistory;
    std::map<std::deque<PlayerChoice::Choice>,std::unordered_map<PlayerChoice::Choice,unsigned long>> historyMap;
};

#endif