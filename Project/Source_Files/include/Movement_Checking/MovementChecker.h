#ifndef MOVEMENT_CHECKER_H
#define MOVEMENT_CHECKER_H

#include "ChessTypes.h"
#include <vector>
#include <set>

class ChessPiece; //Forward Declaration

class MovementChecker{
public:
    virtual ~MovementChecker();

    virtual bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const = 0;
    virtual std::set<BoardCoordinate> getValidMoves(BoardCoordinate current, const std::vector<std::vector<ChessPiece*>>& boardState) const = 0;

    static bool isPositionOnBoard(BoardCoordinate pos);

    static MovementChecker* createMovementChecker(PieceType type);
protected:
    MovementChecker();
};

#endif