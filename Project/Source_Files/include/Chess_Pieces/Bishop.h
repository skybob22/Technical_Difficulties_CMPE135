#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include <mutex>
#include <unordered_map>
#include "wx/wx.h"

class Bishop : public ChessPiece{
public:
    explicit Bishop(ChessPiece::PieceColor color);
    ~Bishop() override;

    bool isMoveValid() override;
    int getPointValue() override;
    wxImage getSprite() override;

private:
    wxImage sprite;

    static std::mutex SpriteMutex;

    const static int BISHOP_POINT_VALUE;
    const static std::unordered_map<ChessPiece::PieceColor,std::string> SPRITE_MAP;
};

#endif