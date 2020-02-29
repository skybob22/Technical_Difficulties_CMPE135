#include <cstdlib>
#include <stdexcept>
#include "Computer.h"

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
 * @brief Used to get the choice of a computer player
 * @returnThe choice that the computer has selected
 */
PlayerChoice::Choice Computer::getPlayerChoice(){
    //Get enum list from PlayerChoice so that it only needs to be updated in PlayerChoice class
    std::vector<PlayerChoice::Choice> choiceList = PlayerChoice::getEnumList();

    int randomChoice = rand()%choiceList.size();
    return choiceList[randomChoice];
}