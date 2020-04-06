#include "Human.h"

/**
 * @brief Constructs a human player object
 * @param playerNumber The number of the player e.g 1 or 2
 */
Human::Human(int playerNumber):Player(playerNumber){
    humanChoice = PlayerChoice::Choice::None;
}

/**
 * @brief Destroys a Human object
 */
Human::~Human() = default;

/**
 * @brief Sets the choice that will be returned by getPlayerChoice(), used by GUI
 * @param choice The choice to be returned next time getPlayerChoice() is called
 */
void Human::setPlayerChoice(PlayerChoice::Choice choice){
    humanChoice = choice;
}

/**
 * @brief Used to get the choice of a human player
 * @return The choice that the user has selected
 */
PlayerChoice::Choice Human::getPlayerChoice(){
    return humanChoice;
}