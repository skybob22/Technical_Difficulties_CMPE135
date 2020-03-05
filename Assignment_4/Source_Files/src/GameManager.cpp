#include <algorithm>
#include <iostream>
#include "GameManager.h"

/**
 * @brief Constructs a GameManager object with the default number of rounds set to 20
 */
GameManager::GameManager():game(nullptr),matchHistory(0),numRounds(20){

}

/**
 * @brief Destroys a GameManager object
 */
GameManager::~GameManager(){
    delete game;
    game = nullptr;
}

/**
 * @brief Sets the number of rounds that the player wants to play
 * @param numberOfRounds The number of rounds to be played
 */
void GameManager::setNumRounds(unsigned int numberOfRounds){
    this->numRounds = numberOfRounds;
}

/**
 * @brief Starts the game and plays the previously set number of rounds
 * @param gameMode The type of gamemode to be use e.g PVP, PVE, or EVE
 */
void GameManager::startGame(Game::GameMode gameMode){
    //Create a new game object with the correct game mode
    game = new Game(gameMode);

    //Clear match history for new round of games, and allocate size for needed number of rounds
    matchHistory.clear();
    matchHistory.reserve(numRounds);

    //Loop through, playing however many rounds were requested
    for(unsigned int i=0;i<numRounds;i++){
        game->playGame();
        matchHistory.push_back(game->getResult());

        //Print out result of game
        std::cout << std::endl << game->getResult() << std::endl;
    }
    delete game;
    game = nullptr;
}

/**
 * @brief Gets the current match history
 * @return A vector containing the win/loss information and player choices
 */
std::vector<GameResult> GameManager::getMatchHistory() const{
    return matchHistory;
}

 /**
  * @brief Prints the current results to an ostream
  * @param stream An ostream object
  * @param gameManager A game manager (preferably that has already run some games)
  * @return A reference to the ostream object
  */
std::ostream& operator<<(std::ostream& stream,const GameManager& gameManager){
    if(gameManager.matchHistory.size() == 0){
        stream << "No Games Played" << std::endl;
        return stream;
    }

    //Look through the match history and total up how many wins each player has
    const unsigned int numPlayers = gameManager.matchHistory[0].playerChoices.size();
    std::vector<unsigned int> numWins(numPlayers,0);
    for(GameResult result : gameManager.matchHistory){
        if(result.winner != 0){
            numWins[result.winner-1]++;
        }
    }

     //Find the player with the most wins while simultaneously checking for ties
     std::vector<unsigned int> maxIndex = {0};
     for(unsigned int i=1;i<numPlayers;i++){
         if (numWins[i] > numWins[maxIndex[0]]){
             maxIndex = {i};
         }
         else if(numWins[i] == numWins[maxIndex[0]]){
             maxIndex.push_back(i);
         }
     }

    //Display how many wins each player has won
    stream << gameManager.matchHistory.size() << " games played" << std::endl;
    for(unsigned int i=0;i<numPlayers;i++){
        stream << "Player " << i+1 << ": " << numWins[i] << " Wins" << std::endl;
    }

    if(maxIndex.size() > 1){
        stream << "Players Tied";
    }
    else {
        stream << "Player " << maxIndex[0]+1 << " Wins!";
    }

    return stream;
}