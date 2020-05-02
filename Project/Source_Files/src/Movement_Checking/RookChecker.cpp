#include "RookChecker.h"
#include "ChessPiece.h"
#include <cmath>

/**
 * @brief Creates a RookChecker object
 */
RookChecker::RookChecker() = default;

/**
 * @brief Destroys a RookChecker object
 */
RookChecker::~RookChecker() = default;

/**
 * @brief Checks if the desired position is valid to move to
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool RookChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const{
    if(dest == current){
        //Staying put is not a valid 'move'
        return false;
    }

    //Make sure desired position is on board
    if(!MovementChecker::isPositionOnBoard(dest)){
        return false;
    }

    //Make sure there is a piece at the target location
    if(boardState[current.y][current.x] == nullptr){
        return false;
    }

    int dx = dest.x - current.x;
    int dy = dest.y - current.y;

    //Check if move is straight or not
    if(dx != 0 && dy != 0){
        return false;
    }

    //Check if there are any pieces blocking the way
    if(dx != 0){
        //Piece is moving along the x-axis
        int unitX = std::copysign(1,dx);

        for (int i = 1; i < abs(dx); i++) {
            if (boardState[current.y][current.x + (unitX*i)] != nullptr) {
                //Another piece is blocking the way
                return false;
            }
        }
    }
    else{
        //Piece is moving along the y-axis
        int unitY = std::copysign(1,dy);

        for (int i = 1; i < abs(dy); i++) {
            if (boardState[current.y + (unitY*i)][current.x] != nullptr) {
                //Another piece is blocking the way
                return false;
            }
        }
    }

    //Lastly, check the destination
    ChessColor myColor = boardState[current.y][current.x]->getColor();
    //Return true if the spot is clear, or there is a piece of the other color that can be taken, else return false
    return boardState[dest.y][dest.x] == nullptr || (boardState[dest.y][dest.x]->getColor() != myColor);
}

std::set<BoardCoordinate> RookChecker::getValidMoves(BoardCoordinate current,const std::vector<std::vector<ChessPiece*>>& boardState) const{
    const std::vector<std::pair<int,int>> possibleDirections = {{1,0},{-1,0},{0,1},{0,-1}};
    std::set<BoardCoordinate> retVal;

    for(auto dir : possibleDirections){
        for(int j=1;;j++){
            int atY = current.y + j*std::get<0>(dir);
            int atX = current.x + j*std::get<1>(dir);

            if(!MovementChecker::isPositionOnBoard(BoardCoordinate(atY,atX))){
                //Position not on board, dont check any further
                break;
            }

            if(boardState[atY][atX] == nullptr){
                //The square is empty, piece can move there
                retVal.insert(BoardCoordinate(atY,atX));
                continue;
            }

            if(boardState[atY][atX]->getColor() != boardState[current.y][current.x]->getColor()){
                //There is a piece of the other color that can be taken
                retVal.insert(BoardCoordinate(atY,atX));
                break;
            }
            else if(boardState[atY][atX]->getColor() == boardState[current.y][current.x]->getColor()){
                //There is a piece of the same color that cannot be taken blocking the way
                break;
            }
        }
    }

    return retVal;
}