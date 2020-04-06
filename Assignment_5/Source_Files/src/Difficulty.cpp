#include "Difficulty.h"
#include <algorithm>

//Define a map that is used to convert an enum into a string (since c++ can't to it automatically)
const std::unordered_map<ComputerDifficulty::Difficulty,std::string> ComputerDifficulty::DIFF_TO_STRING_MAP = {
        {ComputerDifficulty::Difficulty::Easy,"Easy"},
        {ComputerDifficulty::Difficulty::Hard,"Hard"}
};

//Define a map that is used to convert a string into an enum
const std::unordered_map<std::string,ComputerDifficulty::Difficulty> ComputerDifficulty::STRING_TO_DIFF_MAP = {
        {"easy",ComputerDifficulty::Difficulty::Easy},{"e",ComputerDifficulty::Difficulty::Easy},
        {"hard",ComputerDifficulty::Difficulty::Hard},{"h",ComputerDifficulty::Difficulty::Hard}
};

/**
 * @brief Utility function used to convert an enum into a string (used for printing values)
 * @param val A difficulty enum
 * @return The string representing said enum
 * @throws std::invalid_argument If the value is not a valid value
 */
std::string ComputerDifficulty::diffToString(Difficulty val){
    auto searchVal = DIFF_TO_STRING_MAP.find(val);
    if(searchVal != DIFF_TO_STRING_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("Argument is not a valid difficulty enum");
    }
}

/**
 * @brief Utility function used to convert a string into an enum (Used for getting user input)
 * @param val A string representing an enum
 * @return An enum represented by the string
 * @throws std::invalid_argument If the string is not valid, an invalid_argument exception is thrown
 */
ComputerDifficulty::Difficulty ComputerDifficulty::stringToDiff(std::string val){
    std::transform(val.begin(),val.end(),val.begin(),::tolower); //Convert string to lowercase
    auto searchVal = STRING_TO_DIFF_MAP.find(val);
    if(searchVal != STRING_TO_DIFF_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("String does not represent an enum");
    }
}