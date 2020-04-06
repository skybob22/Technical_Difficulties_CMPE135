#include <algorithm>
#include "GameManager.h"

const unsigned int GameManager::DEFAULT_NUM_PLAYERS = 2;

/**
 * @brief Constructs a GameManager object with the default number of rounds set to 20
 */
GameManager::GameManager():game(nullptr),matchHistory(0),numRounds(20){
    currentRound = 0;
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
 * @brief Gets the total number of rounds to be played
 * @return Total number of rounds
 */
unsigned int GameManager::getNumRounds(){
    return numRounds;
}

/**
 * @brief Gets the current round being played (the round that will be played on next button press)
 * @return The current round
 */
unsigned int GameManager::getRound(){
    //TODO: Temporary return value, update to reflect actual game status
    return currentRound;
}

/**
 * @brief Starts the game and plays the previously set number of rounds
 * @param gameMode The type of gamemode to be use e.g PVP, PVE, or EVE
 */
void GameManager::startGame(ComputerDifficulty::Difficulty diff) {
    if(game != nullptr){
        //If a previous game was in progress, stop it
        delete game;
        game = nullptr;
    }

    //Create a new game object with the correct game mode
    game = new Game(diff);
    currentRound = 1;

    //Clear match history for new round of games, and allocate size for needed number of rounds
    matchHistory.clear();
    matchHistory.reserve(numRounds);
}

void GameManager::playRound(){
    if( currentRound <= numRounds && game != nullptr){
        game->playGame();
        matchHistory.push_back(game->getResult());
        currentRound++;
    }

    if(currentRound > numRounds){
        currentRound = 0;
        endGame();
    }
}

/**
 * @brief Stops the current game
 */
void GameManager::endGame(){
    delete game;
    game = nullptr;

    currentRound = 0;
}

/**
 * @brief Checks if there is currently an ongoing game or not
 * @return Whether there is an ongoing game
 */
bool GameManager::isGameInProgress(){
    return game != nullptr;
}

/**
 * @brief Gets the number of wins for each player
 * @return A vector with the number of wins for each player, playerNumber-1 = index
 */
std::vector<unsigned int> GameManager::getNumWins(){
    //Get number of players
    const unsigned int numPlayers = (game != nullptr)?game->getResult().playerChoices.size():DEFAULT_NUM_PLAYERS;
    if(matchHistory.size() == 0){
        //No games played
        return std::vector<unsigned int>(numPlayers+1,0);
    }

    //Look through the match history and total up how many wins each player has
    std::vector<unsigned int> numWins(numPlayers+1,0);
    for(GameResult result : matchHistory){
        numWins[result.winner]++;
    }
    return numWins;
}

/**
 * @brief Gets the number of the player who won the last match
 * @return The player number of the winner, 0 if tied
 */
unsigned int GameManager::getWinner(){
    std::vector<unsigned int> numWins = getNumWins();
    const unsigned int numPlayers = numWins.size()-1;

    //Find the player with the most wins while simultaneously checking for ties
    std::vector<unsigned int> maxIndex = {1};
    for(unsigned int i=2;i<numPlayers+1;i++){
        if (numWins[i] > numWins[maxIndex[0]]){
            maxIndex = {i};
        }
        else if(numWins[i] == numWins[maxIndex[0]]){
            maxIndex.push_back(i);
        }
    }

    if(maxIndex.size() > 1){
        //Players Tied
        return 0;
    }
    else{
        return maxIndex[0];
    }
}

/**
 * @brief Gets the current match history
 * @return A vector containing the win/loss information and player choices
 */
std::vector<GameResult> GameManager::getMatchHistory() const{
    return matchHistory;
}