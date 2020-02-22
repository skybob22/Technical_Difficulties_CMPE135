#include <cstdlib>
#include <stdexcept>
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
    //Used to mitigate bias in random number generation
    int randomChoice = rand()%3;
    switch(randomChoice){
        case 0:{
            return PlayerChoice::Rock;
        }
        case 1:{
            return PlayerChoice::Paper;
        }
        case 2:{
            return PlayerChoice::Scissors;
        }
        default:{
            throw std::runtime_error("Random Number Generator produced unrecognized value");
        }
    }
}