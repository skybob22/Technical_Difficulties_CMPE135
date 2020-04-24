#ifndef ROOK_CHECKER_H
#define ROOK_CHECKER_H

#include "MovementChecker.h"
#include "ChessTypes.h"

class RookChecker : public MovementChecker{
public:
    RookChecker();
    ~RookChecker() override;

    bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const override;
};

#endif