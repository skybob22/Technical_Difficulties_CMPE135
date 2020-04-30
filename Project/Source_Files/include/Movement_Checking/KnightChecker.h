#ifndef KNIGHT_CHECKER_H
#define KNIGHT_CHECKER_H

#include "MovementChecker.h"
#include "ChessTypes.h"

class KnightChecker : public MovementChecker{
public:
    KnightChecker();
    ~KnightChecker() override;

    bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const override;
    std::set<BoardCoordinate> getValidMoves(BoardCoordinate current, const std::vector<std::vector<ChessPiece*>>& boardState) const override;
};

#endif