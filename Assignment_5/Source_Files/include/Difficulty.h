#ifndef COMPUTER_DIFFICULTY_H
#define COMPUTER_DIFFICULTY_H

#include <unordered_map>

class ComputerDifficulty {
public:
    enum Difficulty {
        Easy,
        Hard
    };

    static std::string diffToString(Difficulty val);
    static Difficulty stringToDiff(std::string val);

private:
    static const std::unordered_map<Difficulty,std::string> DIFF_TO_STRING_MAP;
    static const std::unordered_map<std::string,Difficulty> STRING_TO_DIFF_MAP;
};

#endif