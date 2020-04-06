#include <stdexcept>
#include "Game.h"

/**
 * @brief Creates a game object based on the type of gamemode you wish to play
 * @param mode The gamemode e.g PVP (Player vs Player), PVE (Player vs Computer), EVE (Computer vs Computer)
 */
Game::Game(ComputerDifficulty::Difficulty diff):players(2, nullptr){
    //Currently only configured for 2-player, if that changes this will need to be changed
    players[0] = Player::createPlayer(Player::PlayerType::Human,1);
    players[1] = Player::createPlayer(Player::PlayerType::Computer,2,diff);

    //Initialize result to have correct number of players
    result.playerChoices.resize(players.size());
}

/**
 * @brief Destroys a Game object
 */
Game::~Game(){
    //Since player objects were dynamically allocated, loop though pointer list deleting all of them
    for(unsigned int i=0;i<players.size();i++){
        delete players[i];
        players[i] = nullptr;
    }
}

void Game::setPlayerType(unsigned int playerNumber, Player::PlayerType type, ComputerDifficulty::Difficulty diff){
    if(playerNumber-1 > players.size()){
        throw std::length_error("Invalid player number");
    }

    delete players[playerNumber-1];
    players[playerNumber-1] = Player::createPlayer(type,playerNumber,diff);
}

/**
 * @brief Plays a round of rock-paper-scissors
 */
void Game::playGame(){
    //Check if a round has been played or not yet
    if(result.playerChoices.size() < players.size()){
        //If a round hasn't been played reserve enough size for the results
        result.playerChoices.resize(players.size());
    }

    //Get choices from all the players
    for(Player* player : players) {
        result.playerChoices[player->getPlayerNumber()-1] = player->getPlayerChoice();
    }

    //Figure out which player won
    result.winner = gameEval(result.playerChoices);

    //Notify all the players about the result of the match
    for(Player* player : players){
        player->notifyPlayer(result);
    }
}

/**
 * @brief Looks at the players' choices to decide who the winner is
 * @param choices A vector containing all the players' choices
 * @return The winning player (0 = tie)
 */
int Game::gameEval(std::vector<PlayerChoice::Choice> choices){
    if(choices.size() < 2){
        throw std::length_error("Choices vector must have at least 2 elements");
    }

    //Currently only configured for 2-player, if that changes this will need to be changed
    int winner = PlayerChoice::evaluateMatchup(result.playerChoices[0],result.playerChoices[1]);
    if(winner < 0){
        return 1;
    }
    else if(winner > 0){
        return 2;
    }
    else{
        return 0;
    }
}

/**
 * @brief Gets the result of the most recently played round of rock-paper-scissors
 * @return The results of the most recently played round, packaged in a GameResult struct
 */
GameResult Game::getResult() const{
    return result;
}