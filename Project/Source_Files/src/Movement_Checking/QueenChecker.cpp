#include "QueenChecker.h"
#include "ChessPiece.h"

/**
 * @brief Creates a QueenChecker object
 */
QueenChecker::QueenChecker(){
    movementCheckers.reserve(2);
    //Add both rook and bishop to the list of movement checkers used
    movementCheckers.push_back(MovementChecker::createMovementChecker(Rook));
    movementCheckers.push_back(MovementChecker::createMovementChecker(Bishop));
}

/**
 * @brief Destroys a QueenChecker object
 */
QueenChecker::~QueenChecker(){
    for(unsigned int i=0;i<movementCheckers.size();i++){
        delete movementCheckers[i];
        movementCheckers[i] = nullptr;
    }
}

/**
 * @brief Checks if the desired position is valid to move to
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool QueenChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<const ChessPiece*>>& boardState) const{
    //Queen can move like a rook or a bishop, let those checkers do the checking
    for(MovementChecker* checker : movementCheckers){
        if (checker->isMoveValid(current,dest,boardState)){
            return true;
        }
    }
    //If neither rook or bishop found the move was valid, it's probably invalid
    return false;
}

/**
 * @brief Gets a list of all the places the piece can move
 * @param current The current position of the piece
 * @param boardState The board state showing where all the pieces are
 * @return A set containing all the valid positions
 */
std::set<BoardCoordinate> QueenChecker::getValidMoves(BoardCoordinate current, const std::vector<std::vector<const ChessPiece*>>& boardState) const{

}