#include "KnightChecker.h"

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
    //Temporary return value
    return true;
}