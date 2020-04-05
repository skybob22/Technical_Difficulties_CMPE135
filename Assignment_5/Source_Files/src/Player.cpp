#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Player.h"
#include "Human.h"
#include "Computer.h"

//Define a map that is used to convert an enum into a string (since c++ can't to it automatically)
const std::unordered_map<Player::PlayerType,std::string> Player::TYPE_TO_STRING_MAP = {
        {Player::PlayerType::Human,"Human"},
        {Player::PlayerType::Computer,"Computer"}
};

//Define a map that is used to convert a string into an enum
const std::unordered_map<std::string,Player::PlayerType> Player::STRING_TO_TYPE_MAP = {
        {"human",Player::PlayerType::Human},{"h",Player::PlayerType::Human},
        {"computer",Player::PlayerType::Computer},{"c",Player::PlayerType::Computer}
};

/**
 * @brief Initializes various attributes of a player object
 * @param playerNumber The player number e.g 1 or 2
 */
Player::Player(int playerNumber):playerNumber(playerNumber){

}

/**
 * @brief Destroys a player object
 */
Player::~Player() = default;

/**
 * @brief Used to get the player number
 * @return The player number e.g 1 or 2
 */
int Player::getPlayerNumber() const{
    return playerNumber;
}

/**
 * @brief Inform the player of the result of the match
 * @param result The result of the match
 */
void Player::notifyPlayer(const GameResult result){
    //Default behavior = Do nothing
    //Subclasses must implement if functionality is desired
}

/**
 * @brief A factory for creating player objects
 * @param type The type of player that you want to create e.g Human or Computer
 * @param playerNumber The number of the player e.g 1 or 2
 * @return A pointer to a player object of the appropriate type
 */
Player* Player::createPlayer(PlayerType type, int playerNumber){
    switch(type){
        case PlayerType::Human:{
            return new class Human(playerNumber);
        }
        case PlayerType::Computer:{
            std::cout << "Choose Difficulty: 'Easy' (random), or 'Hard' (Machine Learning " << std::endl;
            while(true){
                std::cout << "Difficulty:";
                std::string diffStr;
                std::getline(std::cin, diffStr);

                try{
                    Computer::Difficulty diff = Computer::stringToDiff(diffStr);
                    return Computer::createComputer(diff,playerNumber);
                }
                catch(std::invalid_argument& e){
                    std::cout << "Invalid option, please try again" << std::endl;
                }
            }
        }
        default:{
            throw std::invalid_argument("Player must be either Human or Computer");
        }
    }//End switch
}

/**
 * @brief Utility function used to convert an enum into a string (used for printing values)
 * @param val A difficulty enum
 * @return The string representing said enum
 * @throws std::invalid_argument If the value is not a valid value
 */
std::string Player::typeToString(PlayerType val){
    auto searchVal = TYPE_TO_STRING_MAP.find(val);
    if(searchVal != TYPE_TO_STRING_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("Argument is not a valid playertype enum");
    }
}

/**
 * @brief Utility function used to convert a string into an enum (Used for getting user input)
 * @param val A string representing an enum
 * @return An enum represented by the string
 * @throws std::invalid_argument If the string is not valid, an invalid_argument exception is thrown
 */
Player::PlayerType Player::stringToType(std::string val){
    std::transform(val.begin(),val.end(),val.begin(),::tolower); //Convert string to lowercase
    auto searchVal = STRING_TO_TYPE_MAP.find(val);
    if(searchVal != STRING_TO_TYPE_MAP.end()){
        return searchVal->second;
    }
    else{
        throw std::invalid_argument("String does not represent an enum");
    }
}