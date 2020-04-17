#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"
#include <mutex>
#include <unordered_map>
#include "wx/wx.h"

class Knight : public ChessPiece{
public:
    explicit Knight(ChessPiece::PieceColor color);
    ~Knight() override;

    bool isMoveValid() override;
    int getPointValue() override;
    wxImage getSprite() override;

private:
    wxImage sprite;

    static std::mutex SpriteMutex;

    const static int KNIGHT_POINT_VALUE;
    const static std::unordered_map<ChessPiece::PieceColor,std::string> SPRITE_MAP;
};

#endif