#include "Human.h"
#include <iostream>

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
PlayerChoice::Choice Human::getPlayerChoice(){
    std::vector<PlayerChoice::Choice> validOptions = PlayerChoice::getEnumList();
    std::string choiceList;
    for(unsigned int i=0;i<validOptions.size();i++){
        choiceList += PlayerChoice::toString(validOptions[i]);
        if(i < validOptions.size()-1){
            choiceList += ", ";
        }
        if(i == validOptions.size()-2){
            choiceList += "or ";
        }
    }
    std::cout << "Select Option: Options are " << choiceList << std::endl;

    std::string userInput;
    while(true) {
        std::cout << "Player " << getPlayerNumber() << ":";
        std::getline(std::cin,userInput);

        try{
            return PlayerChoice::stringToChoice(userInput);
        }
        catch(std::invalid_argument& e){
            std::cout << "Invalid option, please try again" << std::endl;
        }
    }
}