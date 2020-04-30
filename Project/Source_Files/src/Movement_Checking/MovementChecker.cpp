#include "GameManager.h"
#include "MovementChecker.h"
#include "BishopChecker.h"
#include "KingChecker.h"
#include "KnightChecker.h"
#include "PawnChecker.h"
#include "QueenChecker.h"
#include "RookChecker.h"

/**
 * @brief Creates a MovementChecker object
 */
MovementChecker::MovementChecker() = default;

/**
 * @brief Destroys a MovementChecker object
 */
MovementChecker::~MovementChecker() = default;

/**
 * @brief Checks to see if a position is on the board or not
 * @param pos The desired coordinates
 * @return Whether the position is on the board or not
 */
bool MovementChecker::isPositionOnBoard(BoardCoordinate pos){
    return (pos.x >= 0 && pos.x < static_cast<int>(GameManager::getBoardWidth())) && (pos.y >=0 && pos.y < static_cast<int>(GameManager::getBoardHeight()));
}

/**
 * @brief A factory method for creating different MovementCheckers for different kinds of pieces
 * @param type The type of piece
 * @return A pointer to the appropriate type of movement checker
 */
MovementChecker* MovementChecker::createMovementChecker(PieceType type){
    switch(type){
        case Bishop:
            return new BishopChecker;
            break;
        case King:
            return new KingChecker;
            break;
        case Knight:
            return new KnightChecker;
            break;
        case Pawn:
            return new PawnChecker;
            break;
        case Queen:
            return new QueenChecker;
            break;
        case Rook:
            return new RookChecker;
            break;
        default:
            return nullptr;
            break;
    }
}