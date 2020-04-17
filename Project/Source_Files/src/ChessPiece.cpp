#include "ChessPiece.h"

const std::string ChessPiece::SPRITE_DIRECTORY = "./Sprites/PNG/";

ChessPiece::ChessPiece(ChessPiece::PieceColor color):color(color){

}

ChessPiece::~ChessPiece() = default;

ChessPiece::PieceColor ChessPiece::getColor() {
    return color;
}