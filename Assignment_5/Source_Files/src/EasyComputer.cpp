#include "EasyComputer.h"

/**
 * @brief Constructs an EasyComputer object
 * @param playerNum The player number (1,2,...)
 */
EasyComputer::EasyComputer(int playerNum):Computer(playerNum){

}

/**
 * @brief Destroys and EasyComputer object
 */
EasyComputer::~EasyComputer() = default;

/**
 * @brief Gets the choice (easy difficulty)
 * @return The choice (Rock,Paper,Scissors...)
 */
PlayerChoice::Choice EasyComputer::getPlayerChoice(){
    return Computer::getRandomChoice();
}