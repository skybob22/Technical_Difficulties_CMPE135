#include "BishopChecker.h"

/**
 * @brief Creates a BishopChecker object
 */
BishopChecker::BishopChecker() = default;

/**
 * @brief Destroys a BishopChecker object
 */
BishopChecker::~BishopChecker() = default;

/**
 * @brief Checks if the desired position is valid to move to
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool BishopChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState){
    //Temporary return value
    return true;
}