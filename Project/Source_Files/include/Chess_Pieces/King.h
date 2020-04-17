#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include <mutex>
#include <unordered_map>
#include "wx/wx.h"

class King : public ChessPiece{
public:
    explicit King(ChessPiece::PieceColor color);
    ~King() override;

    bool isMoveValid() override;
    int getPointValue() override;
    wxImage getSprite() override;

private:
    wxImage sprite;

    static std::mutex SpriteMutex;

    const static int KING_POINT_VALUE;
    const static std::unordered_map<ChessPiece::PieceColor,std::string> SPRITE_MAP;
};

#endif