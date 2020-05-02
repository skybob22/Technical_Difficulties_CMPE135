#include "KingChecker.h"
#include "ChessPiece.h"
#include <cmath>

/**
 * @brief Creates a KingChecker object
 */
KingChecker::KingChecker() = default;

/**
 * @brief Destroys a KingChecker object
 */
KingChecker::~KingChecker() = default;

/**
 * @brief Checks if the desired position is valid to move to (doesn't include checking for check/checkmate)
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool KingChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const{
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

    //King can only move 1 space at a time
    if(abs(dx) > 1 || abs(dy) > 1){
        return false;
    }

    //Lastly, check the destination
    ChessColor myColor = boardState[current.y][current.x]->getColor();
    //Return true if the spot is clear, or there is a piece of the other color that can be taken, else return false
    return boardState[dest.y][dest.x] == nullptr || (boardState[dest.y][dest.x]->getColor() != myColor);
}

/**
 * @brief Gets a list of all the places the piece can move (doesn't include checking for check/checkmate)
 * @param current The current position of the piece
 * @param boardState The board state showing where all the pieces are
 * @return A set containing all the valid positions
 */
std::set<BoardCoordinate> KingChecker::getValidMoves(BoardCoordinate current, const std::vector<std::vector<ChessPiece*>>& boardState) const{
    const std::vector<std::pair<int,int>> possibleDirections = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    std::set<BoardCoordinate> retVal;

    for(auto pos : possibleDirections){
        int atY = current.y + std::get<0>(pos);
        int atX = current.x + std::get<1>(pos);

        if(!MovementChecker::isPositionOnBoard(BoardCoordinate(atY,atX))){
            //Square is not on board
            continue;
        }

        if(boardState[atY][atX] == nullptr){
            //The square is empty, piece can move there
            retVal.insert(BoardCoordinate(atY,atX));
            continue;
        }

        if(boardState[atY][atX]->getColor() != boardState[current.y][current.x]->getColor()){
            //There is a piece of the other color that can be taken
            retVal.insert(BoardCoordinate(atY,atX));
            continue;
        }
        else if(boardState[atY][atX]->getColor() == boardState[current.y][current.x]->getColor()){
            //There is a piece of the same color that cannot be taken blocking the way
            continue;
        }
    }

    return retVal;
}