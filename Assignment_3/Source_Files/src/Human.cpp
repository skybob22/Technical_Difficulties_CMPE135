#include "Human.h"

/**
 * @brief Constructs a human player object
 * @param playerNumber The number of the player e.g 1 or 2
 */
Human::Human(int playerNumber):Player(playerNumber){

}

/**
 * @brief Destroys a Human object
 */
Human::~Human() = default;

/**
 * @brief Used to get the choice of a human player
 * @return The choice that the user has selected
 */
PlayerChoice Human::getPlayerChoice(){
    //Temporary measure until implemented
    return PlayerChoice::Rock;
}