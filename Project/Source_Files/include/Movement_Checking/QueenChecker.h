#ifndef QUEEN_CHECKER_H
#define QUEEN_CHECKER_H

#include "MovementChecker.h"
#include "ChessTypes.h"

class QueenChecker : public MovementChecker{
public:
    QueenChecker();
    ~QueenChecker() override;

    bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) override;
private:
    std::vector<MovementChecker*> movementCheckers;
};

#endif