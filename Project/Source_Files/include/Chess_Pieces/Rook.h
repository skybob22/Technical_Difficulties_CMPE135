#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
#include <mutex>
#include <unordered_map>
#include "wx/wx.h"

class Rook : public ChessPiece{
public:
    explicit Rook(ChessPiece::PieceColor color);
    ~Rook() override;

    bool isMoveValid() override;
    int getPointValue() override;
    wxImage getSprite() override;

private:
    wxImage sprite;

    static std::mutex SpriteMutex;

    const static int ROOK_POINT_VALUE;
    const static std::unordered_map<ChessPiece::PieceColor,std::string> SPRITE_MAP;
};

#endif