#include "KnightChecker.h"
#include "ChessPiece.h"
#include <cmath>

/**
 * @brief Creates a KnightChecker object
 */
KnightChecker::KnightChecker() = default;

/**
 * @brief Destroys a KnightChecker object
 */
KnightChecker::~KnightChecker() = default;

/**
 * @brief Checks if the desired position is valid to move to
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool KnightChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const{
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

    //Check if move is L shape or not
    if(!(abs(dx) == 1 && abs(dy) == 2) && !(abs(dx) == 2 && abs(dy) == 1)){
        return false;
    }

    //Dont need to check if pieces are in the way, since knight moves by jumping
    ChessColor myColor = boardState[current.y][current.x]->getColor();
    //Return true if the spot is clear, or there is a piece of the other color that can be taken, else return false
    return boardState[dest.y][dest.x] == nullptr || (boardState[dest.y][dest.x]->getColor() != myColor);
}

/**
 * @brief Gets a list of all the places the piece can move
 * @param current The current position of the piece
 * @param boardState The board state showing where all the pieces are
 * @return A set containing all the valid positions
 */
std::set<BoardCoordinate> KnightChecker::getValidMoves(BoardCoordinate current, const std::vector<std::vector<ChessPiece*>>& boardState) const{
    const std::vector<std::pair<int,int>> possibleDirections = {{1,1},{1,-1},{-1,1},{-1,-1}};
    const std::vector<std::pair<int,int>> possibleMagnitude = {{1,2},{2,1}};
    std::set<BoardCoordinate> retVal;

    for(auto dir : possibleDirections){
        for(auto mag :possibleMagnitude){
            int atY = current.y + std::get<0>(dir)*std::get<0>(mag);
            int atX = current.x + std::get<1>(dir)*std::get<1>(mag);

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
    }

    return retVal;
}