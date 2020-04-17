#include "Bishop.h"
#include <iostream>

std::mutex Bishop::SpriteMutex;

const std::unordered_map<ChessPiece::PieceColor,std::string> Bishop::SPRITE_MAP = {
        {ChessPiece::PieceColor::White,SPRITE_DIRECTORY + "Bishop_W.png"},
        {ChessPiece::PieceColor::Black,SPRITE_DIRECTORY + "Bishop_B.png"}
};
const int Bishop::BISHOP_POINT_VALUE = 3;

Bishop::Bishop(ChessPiece::PieceColor color):ChessPiece(color){
    std::lock_guard<std::mutex> fileLock(Bishop::SpriteMutex);
    auto pathResult = SPRITE_MAP.find(color);
    if(pathResult != SPRITE_MAP.end()){
        sprite = wxImage(pathResult->second);
    }
    else{
        throw std::invalid_argument("That is not a valid color");
    }
}

Bishop::~Bishop() = default;

bool Bishop::isMoveValid(){
    //Temporary value
    return false;
}

int Bishop::getPointValue(){
    return BISHOP_POINT_VALUE;
}

wxImage Bishop::getSprite(){
    return sprite;
}