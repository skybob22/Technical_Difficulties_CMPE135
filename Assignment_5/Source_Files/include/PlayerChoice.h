#ifndef PLAYER_CHOICE_H
#define PLAYER_CHOICE_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

class PlayerChoice{
public:
    enum Choice{
        Rock,
        Paper,
        Scissors
    };

    static int evaluateMatchup(Choice p1,Choice p2);

    static std::vector<Choice> getEnumList();
    static std::string toString(Choice val);
    static Choice stringToChoice(std::string val);

private:
    //Constructor declared private so that class cannot be instantiated
    PlayerChoice();
    ~PlayerChoice();

    static const std::unordered_map<Choice,std::unordered_set<Choice>> MATCHUP_MAP;
    static const std::unordered_map<Choice,std::string> CHOICE_TO_STRING_MAP;
    static const std::unordered_map<std::string,Choice> STRING_TO_CHOICE_MAP;
};

#endif