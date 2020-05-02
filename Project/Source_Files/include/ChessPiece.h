#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessTypes.h"
#include "MovementChecker.h"
#include <string>
#include <unordered_map>
#include <wx/wx.h>

class ChessPiece{
public:
    ChessPiece(ChessColor color,PieceType type,BoardCoordinate position);
    ChessPiece(const ChessPiece& other);
    ~ChessPiece();

    //TODO: Do we want to have each piece have a pointer to the board state or pass it it when checking moves?
    bool isMoveValid(BoardCoordinate pos,const std::vector<std::vector<ChessPiece*>>& boardState) const;
    std::set<BoardCoordinate> getValidMoves(const std::vector<std::vector<ChessPiece*>>& boardState) const;
    void move(BoardCoordinate pos); //TODO: Check if position is valid when moving, need to somehow get reference to board state

    int getPointValue() const;
    wxImage getSprite() const;

    ChessColor getColor() const;
    PieceType getPieceType() const;
    BoardCoordinate getPosition() const;

private:
    MovementChecker* moveChecker;
    BoardCoordinate position;
    ChessColor color;
    PieceType type;
    wxImage sprite;

    const static std::string SPRITE_DIRECTORY;
    const static std::unordered_map<PieceType,std::unordered_map<ChessColor,std::string>> SPRITE_PATH_MAP;
    const static std::unordered_map<PieceType,int> POINT_VALUE_MAP;
};

#endif