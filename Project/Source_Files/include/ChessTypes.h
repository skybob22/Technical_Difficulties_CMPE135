#ifndef CHESS_ENUMS_H
#define CHESS_ENUMS_H

enum ChessColor{
    White,
    Black
};

enum PieceType{
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn
};

struct BoardCoordinate{
    int x;
    int y;
    BoardCoordinate(unsigned int y,unsigned int x):x(x),y(y){};

    bool operator == (const BoardCoordinate& rhs) const{
        return x == rhs.x && y == rhs.y;
    }
    bool operator < (const BoardCoordinate& rhs) const{
        return (x + 8*y) < (rhs.x + 8*rhs.y);
    }
};

#endif