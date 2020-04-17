#include "Pawn.h"
#include <iostream>

std::mutex Pawn::SpriteMutex;

const std::unordered_map<ChessPiece::PieceColor,std::string> Pawn::SPRITE_MAP = {
        {ChessPiece::PieceColor::White,SPRITE_DIRECTORY + "Pawn_W.png"},
        {ChessPiece::PieceColor::Black,SPRITE_DIRECTORY + "Pawn_B.png"}
};
const int Pawn::PAWN_POINT_VALUE = 1;

Pawn::Pawn(ChessPiece::PieceColor color):ChessPiece(color){
    std::lock_guard<std::mutex> fileLock(Pawn::SpriteMutex);
    auto pathResult = SPRITE_MAP.find(color);
    if(pathResult != SPRITE_MAP.end()){
        sprite = wxImage(pathResult->second);
    }
    else{
        throw std::invalid_argument("That is not a valid color");
    }
}

Pawn::~Pawn() = default;

bool Pawn::isMoveValid(){
    //Temporary value
    return false;
}

int Pawn::getPointValue(){
    return PAWN_POINT_VALUE;
}

wxImage Pawn::getSprite(){
    return sprite;
}