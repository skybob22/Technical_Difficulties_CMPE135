#include <stdexcept>
#include "Game.h"

/**
 * @brief Creates a game object based on the type of gamemode you wish to play
 * @param mode The gamemode e.g PVP (Player vs Player), PVE (Player vs Computer), EVE (Computer vs Computer)
 */
Game::Game(GameMode mode):players(2, nullptr){
    switch(mode){
        case GameMode::PVP:{
            players[0] = Player::createPlayer(Player::PlayerType::Human,1);
            players[1] = Player::createPlayer(Player::PlayerType::Human,2);
            break;
        }
        case GameMode::PVE:{
            players[0] = Player::createPlayer(Player::PlayerType::Human,1);
            players[1] = Player::createPlayer(Player::PlayerType::Computer,2);
            break;
        }
        case GameMode::EVE:{
            players[0] = Player::createPlayer(Player::PlayerType::Computer,1);
            players[1] = Player::createPlayer(Player::PlayerType::Computer,2);
            break;
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
        result.playerChoices.resize(players.size());
    }

    for(Player* player: players) {
        result.playerChoices[player->getPlayerNumber()-1] = player->getPlayerChoice();
    }

    //Currently only configured for 2-player, if that changes this will need to be changed
    int winner = PlayerChoice::evaluateMatchup(result.playerChoices[0],result.playerChoices[1]);
    if(winner < 0){
        result.winner = 1;
    }
    else if(winner > 0){
        result.winner = 2;
    }
    else{
        result.winner = 0;
    }
}

/**
 * @brief Gets the result of the most recently played round of rock-paper-scissors
 * @return The results of the most recently played round, packaged in a GameResult struct
 */
Game::GameResult Game::getResult() const{
    return result;
}

/**
 * @brief Prints the result to an ostream
 * @param result A GameResult object
 * @return A reference to the stream object
 */
std::ostream& operator<<(std::ostream& stream,Game::GameResult result){
    if(result.playerChoices.size() == 0){
        stream << "No Results" << std::endl;
        return stream;
    }

    for(unsigned int i=0;i<result.playerChoices.size();i++){
        stream << "Player " << i+1 << ": " << PlayerChoice::toString(result.playerChoices[i]) << std::endl;
    }

    //Check if players tied
    if(result.winner == 0){
        stream << "Players Tied" << std::endl;
    }
    else {
        stream << "Player " << result.winner << " Wins!" << std::endl;
    }
    return stream;
}