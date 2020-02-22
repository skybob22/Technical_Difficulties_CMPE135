#include <stdexcept>
#include "Player.h"
#include "Human.h"
#include "Computer.h"

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
            return new class Computer(playerNumber);
        }
        default:{
            throw std::invalid_argument("Player must be either Human or Computer");
        }
    }//End switch
}