#ifndef BISHOP_CHECKER_H
#define BISHOP_CHECKER_H

#include "MovementChecker.h"
#include "ChessTypes.h"

class BishopChecker : public MovementChecker{
public:
    BishopChecker();
    ~BishopChecker() override;

    bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const override;
};

#endif