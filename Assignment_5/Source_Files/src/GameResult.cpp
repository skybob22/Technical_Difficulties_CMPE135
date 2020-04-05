#include "GameResult.h"

/**
 * @brief Constructs a GameResult object
 */
GameResult::GameResult():playerChoices(0),winner(0){

}

/**
 * @brief Destroys a GameResult object
 */
GameResult::~GameResult() = default;

/**
 * @brief Prints the result to an ostream
 * @param result A GameResult object
 * @return A reference to the stream object
 */
std::ostream& operator<<(std::ostream& stream,GameResult result){
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
        stream << "Player " << result.winner << " Wins!";
    }
    return stream;
}