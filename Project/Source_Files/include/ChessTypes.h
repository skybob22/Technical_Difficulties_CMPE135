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
    unsigned int x;
    unsigned int y;
    BoardCoordinate(unsigned int y,unsigned int x):x(x),y(y){};
};

#endif