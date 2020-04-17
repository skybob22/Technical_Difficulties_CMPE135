#include "Rook.h"
#include <iostream>

std::mutex Rook::SpriteMutex;

const std::unordered_map<ChessPiece::PieceColor,std::string> Rook::SPRITE_MAP = {
        {ChessPiece::PieceColor::White,SPRITE_DIRECTORY + "Rook_W.png"},
        {ChessPiece::PieceColor::Black,SPRITE_DIRECTORY + "Rook_B.png"}
};
const int Rook::ROOK_POINT_VALUE = 5;

Rook::Rook(ChessPiece::PieceColor color):ChessPiece(color){
    std::lock_guard<std::mutex> fileLock(Rook::SpriteMutex);
    auto pathResult = SPRITE_MAP.find(color);
    if(pathResult != SPRITE_MAP.end()){
        sprite = wxImage(pathResult->second);
    }
    else{
        throw std::invalid_argument("That is not a valid color");
    }
}

Rook::~Rook() = default;

bool Rook::isMoveValid(){
    //Temporary value
    return false;
}

int Rook::getPointValue(){
    return ROOK_POINT_VALUE;
}

wxImage Rook::getSprite(){
    return sprite;
}