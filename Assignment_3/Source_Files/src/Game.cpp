#include <stdexcept>
#include "Game.h"
#include "WinEval.h"

/**
 * @brief Creates a game object based on the type of gamemode you wish to play
 * @param mode The gamemode e.g PVP (Player vs Player), PVE (Player vs Computer), EVE (Computer vs Computer)
 */
Game::Game(GameMode mode):players(2, nullptr){
    switch(mode){
        case GameMode::PVP:{
            players[0] = Player::createPlayer(Player::PlayerType::Human,1);
            players[1] = Player::createPlayer(Player::PlayerType::Human,2);
        }
        case GameMode::PVE:{
            players[0] = Player::createPlayer(Player::PlayerType::Human,1);
            players[0] = Player::createPlayer(Player::PlayerType::Computer,2);
        }
        case GameMode::EVE:{
            players[0] = Player::createPlayer(Player::PlayerType::Computer,1);
            players[0] = Player::createPlayer(Player::PlayerType::Computer,2);
        }
        default:{
            throw std::invalid_argument("Gamemode must be PVP, PVE or EVE");
        }
    }//End switch
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

/**
 * @brief Plays a round of rock-paper-scissors
 */
void Game::playGame(){
    //Check if a round has been played or not yet
    if(result.playerChoices.size() < players.size()){
        //If a round hasn't been played reserve enough size for the results
        result.playerChoices.reserve(players.size());
    }

    for(unsigned int i=0;i<players.size();i++) {
        result.playerChoices[i] = players[i]->getPlayerChoice();
    }
    result.winner = WinEval::checkResult(result.playerChoices);
}

/**
 * @brief Gets the result of the most recently played round of rock-paper-scissors
 * @return The results of the most recently played round, packaged in a GameResult struct
 */
Game::GameResult Game::getResult() const{
    return result;
}