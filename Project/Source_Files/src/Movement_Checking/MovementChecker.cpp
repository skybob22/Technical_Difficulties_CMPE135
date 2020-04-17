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