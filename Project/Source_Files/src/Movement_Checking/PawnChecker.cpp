#include "PawnChecker.h"

/**
 * @brief Creates a PawnChecker object
 */
PawnChecker::PawnChecker() = default;

/**
 * @brief Destroys a PawnChecker object
 */
PawnChecker::~PawnChecker() = default;

/**
 * @brief Checks if the desired position is valid to move to
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool PawnChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const{
    //Temporary return value
    return true;
}