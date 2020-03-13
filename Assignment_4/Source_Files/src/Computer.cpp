#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include "Computer.h"
#include "EasyComputer.h"
#include "HardComputer.h"

//Define a map that is used to convert an enum into a string (since c++ can't to it automatically)
const std::unordered_map<Computer::Difficulty,std::string> Computer::DIFF_TO_STRING_MAP = {
        {Computer::Difficulty::Easy,"Easy"},
        {Computer::Difficulty::Hard,"Hard"}
};

//Define a map that is used to convert a string into an enum
const std::unordered_map<std::string,Computer::Difficulty> Computer::STRING_TO_DIFF_MAP = {
        {"easy",Computer::Difficulty::Easy},{"e",Computer::Difficulty::Easy},
        {"hard",Computer::Difficulty::Hard},{"h",Computer::Difficulty::Hard}
};

/**
 * @brief Constructs a computer player object
 * @param playerNumber The number of the player e.g 1 or 2
 */
Computer::Computer(int playerNumber):Player(playerNumber){
    //Set the rand seed to produce more random results
    srand(time(NULL));
}

/**
 * @brief Destroys a Computer object
 */
Computer::~Computer() = default;

/**
 * @brief A factory for creating computer objects
 * @param diff The difficulty (based on difficulty enum, Easy, Hard,...)
 * @param playerNum The player number (1,2,...)
 * @return A pointer to a computer of the appropriate difficulty
 */
Computer* Computer::createComputer(Difficulty diff, int playerNum){
    switch (diff){
        case Easy:{
            return  new EasyComputer(playerNum);
        }
        case Hard:{
            return new HardComputer(playerNum);
        }
        default:{
            throw std::invalid_argument("Computer difficulty must be either Easy or Hard");
        }
    } //End Switch
}

/**
 * @brief Used to get the choice of a computer player
 * @returnThe choice that the computer has selected
 */
PlayerChoice::Choice Computer::getRandomChoice(){
    //Get enum list from PlayerChoice so that it only needs to be updated in PlayerChoice class
    std::vector<PlayerChoice::Choice> choiceList = PlayerChoice::getEnumList();

    unsigned int randomChoice = rand()%choiceList.size();
    return choiceList[randomChoice];
}

/**
 * @brief Utility function used to convert an enum into a string (used for printing values)
 * @param val A difficulty enum
 * @return The string representing said enum
 * @throws std::invalid_argument If the value is not a valid value
 */
std::string Computer::diffToString(Difficulty val){
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
Computer::Difficulty Computer::stringToDiff(std::string val){
    std::transform(val.begin(),val.end(),val.begin(),::tolower); //Convert string to lowercase
    auto searchVal = STRING_TO_DIFF_MAP.find(val);
    if(searchVal != STRING_TO_DIFF_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("String does not represent an enum");
    }
}