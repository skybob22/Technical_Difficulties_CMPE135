#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <wx/wx.h>

//TODO: Refactor the current ChessPiece implementation (too much repeated code between subclasses)
//Currently only relies on public interface, so we can change the subclasses all we want, maybe add a factory
//Possibly add enum for piece type and move point map to base class. See if we can do composition over inheritance

class ChessPiece{
public:
    enum PieceColor{
        White,
        Black
    };

    virtual ~ChessPiece();

    virtual bool isMoveValid() = 0;
    virtual int getPointValue() = 0;
    virtual wxImage getSprite() = 0;

    PieceColor getColor();
protected:
    //TODO: Figure out what data structures to store state information
    explicit ChessPiece(PieceColor color);

    const static std::string SPRITE_DIRECTORY;

private:
    PieceColor color;
};

#endif