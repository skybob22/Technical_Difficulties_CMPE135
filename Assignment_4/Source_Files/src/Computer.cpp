#include <cstdlib>
#include <stdexcept>
#include "Computer.h"
#include "EasyComputer.h"
#include "HardComputer.h"

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