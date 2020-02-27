#include "PlayerChoice.h"
#include <algorithm>

//Define the matchups for what wins against what
//Format {Choice,{Everything choice beats}}
const std::unordered_map<PlayerChoice::Choice,std::unordered_set<PlayerChoice::Choice>> PlayerChoice::MATCHUP_MAP = {
        {Rock,{Scissors}},
        {Paper,{Rock}},
        {Scissors,{Paper}}
};

//Define a map that is used to convert an enum into a string (since c++ can't to it automatically)
const std::unordered_map<PlayerChoice::Choice,std::string> PlayerChoice::CHOICE_TO_STRING_MAP = {
        {Rock,"Rock"},
        {Paper,"Paper"},
        {Scissors,"Scissors"}
};

//Define a map that is used to convert a string into an enum
const std::unordered_map<std::string,PlayerChoice::Choice> PlayerChoice::STRING_TO_CHOICE_MAP = {
        {"rock",Rock},{"r",Rock},
        {"paper",Paper},{"p",Paper},
        {"scissors",Scissors},{"s",Scissors}
};

/**
 * @brief Constructs a PlayerChoice object
 */
PlayerChoice::PlayerChoice() = default;

/**
 * @brief Destorys a PlayerChoice object
 */
PlayerChoice::~PlayerChoice() = default;

/**
 * @brief Used to look at a set of player choices and determine which one won the match
 * @param playerInputs A vector of player choices index[0] = player one choice, index[1] = player two choice
 * @return Which player won the match, 0 = tie, -1 = player one wins, -2 = player two wins
 */
int PlayerChoice::evaluateMatchup(Choice p1, Choice p2){
    //Check if player 1 beat player 2
    auto p1Check = MATCHUP_MAP.find(p1);
    if(p1Check != MATCHUP_MAP.end()){
        if(p1Check->second.find(p2) != p1Check->second.end()){
            //Player 1 beat player 2
            return -1;
        }
    }

    //Check if player 2 beat player 1
    auto p2Check = MATCHUP_MAP.find(p2);
    if(p2Check != MATCHUP_MAP.end()){
        if(p2Check->second.find(p1) != p2Check->second.end()){
            //Player 1 beat player 2
            return 1;
        }
    }

    //If neither, they must have both picked the same thing and tied
    return 0;
}

/**
 * @brief Utility function to convert an enum into a string representing that enum (used for printing messages)
 * @param val The value of the enum
 * @return A string representing said enum value
 */
std::string PlayerChoice::toString(PlayerChoice::Choice val){
    auto searchVal = CHOICE_TO_STRING_MAP.find(val);
    if(searchVal != CHOICE_TO_STRING_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("Argument is not a valid choice enum");
    }
}

/**
 * @brief Utility function to convert a string into an enum (used for getting user input)
 * @param val A string representing an enum
 * @return An enum matching said string
 * @throws invalid_argument If the string is not valid, an invalid_argument exception is thrown
 */
PlayerChoice::Choice PlayerChoice::stringToChoice(std::string val){
    std::transform(val.begin(),val.end(),val.begin(),[](char c){return tolower(c);}); //Convert string to lower case
    auto searchVal = STRING_TO_CHOICE_MAP.find(val);
    if(searchVal != STRING_TO_CHOICE_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("String does not represent an enum");
    }
}

/**
 * @brief Utility function to get a list containing all the valid enums
 * @return A vector containing 1 of each valid enum
 */
 //Must be hardcoded since C++ doesn't have a way to iterate over enums
std::vector<PlayerChoice::Choice> PlayerChoice::getEnumList(){
    return {Rock,Paper,Scissors};
}