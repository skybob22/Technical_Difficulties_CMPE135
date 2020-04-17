#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include <mutex>
#include <unordered_map>
#include "wx/wx.h"

class Pawn : public ChessPiece{
public:
    explicit Pawn(ChessPiece::PieceColor color);
    ~Pawn() override;

    bool isMoveValid() override;
    int getPointValue() override;
    wxImage getSprite() override;

private:
    wxImage sprite;

    static std::mutex SpriteMutex;

    const static int PAWN_POINT_VALUE;
    const static std::unordered_map<ChessPiece::PieceColor,std::string> SPRITE_MAP;
};

#endif