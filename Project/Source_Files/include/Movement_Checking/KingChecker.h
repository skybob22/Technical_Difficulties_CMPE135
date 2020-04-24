#ifndef KING_CHECKER_H
#define King_CHECKER_H

#include "MovementChecker.h"
#include "ChessTypes.h"

class KingChecker : public MovementChecker{
public:
    KingChecker();
    ~KingChecker() override;

    bool isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const override;
};

#endif