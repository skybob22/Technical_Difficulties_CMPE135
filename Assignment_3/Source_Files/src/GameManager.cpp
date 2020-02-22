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
    matchHistory = std::vector<Game::GameResult>(0);
    matchHistory.reserve(numRounds);

    //Loop through, playing however many rounds were requested
    for(unsigned int i=0;i<numRounds;i++){
        game->playGame();
        matchHistory[i] = game->getResult();
    }
    delete game;
    game = nullptr;
}

/**
 * @brief Gets the current match history
 * @return A vector containing the win/loss information and player choices
 */
std::vector<Game::GameResult> GameManager::getMatchHistory() const{
    return matchHistory;
}

/**
 * @brief Prints the current results to an ostream
 */
std::ostream& GameManager::operator<<(std::ostream& stream) const{
    //TODO: Add code to display results
    return stream;
}