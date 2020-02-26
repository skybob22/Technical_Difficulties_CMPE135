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
PlayerChoice Human::getPlayerChoice(){
    //TODO: Write code to get choice from user
    char choice;
    std::cout << "Rock, Paper, or Scissors? Press r, p, or s respectively: " << std::endl;

    // Is this technically what we're supposed to do? I feel like there's more encapsulation we can do to avoid having to add more cases here?
    while(1) {
        std::cin >> choice;

        switch (choice) {
            case 'r':
                return PlayerChoice::Rock;
            case 'p':
                return PlayerChoice::Paper;
            case 's':
                return PlayerChoice::Scissors;
        }
        std::cout << "Invalid choice, please try again: " << std::endl;
    }
}