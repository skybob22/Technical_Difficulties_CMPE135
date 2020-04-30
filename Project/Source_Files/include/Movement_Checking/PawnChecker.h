#ifndef PAWN_CHECKER_H
#define PAWN_CHECKER_H

#include "MovementChecker.h"
#include "ChessTypes.h"

class PawnChecker : public MovementChecker{
public:
    PawnChecker();
    ~PawnChecker() override;

    bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const override;
    std::set<BoardCoordinate> getValidMoves(BoardCoordinate current, const std::vector<std::vector<ChessPiece*>>& boardState) const override;

private:
    const static std::set<BoardCoordinate> WHITE_STARTING_POS,BLACK_STARTING_POS;
};

#endif