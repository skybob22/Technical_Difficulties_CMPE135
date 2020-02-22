#include "Computer.h"

/**
 * @brief Constructs a computer player object
 * @param playerNumber The number of the player e.g 1 or 2
 */
Computer::Computer(int playerNumber):Player(playerNumber){

}

/**
 * @brief Destroys a Computer object
 */
Computer::~Computer() = default;

/**
 * @brief Used to get the choice of a computer player
 * @returnThe choice that the computer has selected
 */
PlayerChoice Computer::getPlayerChoice(){
    //Temporary measure until implemented
    return PlayerChoice::Rock;
}