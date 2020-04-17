#include "Queen.h"
#include <iostream>

std::mutex Queen::SpriteMutex;

const std::unordered_map<ChessPiece::PieceColor,std::string> Queen::SPRITE_MAP = {
        {ChessPiece::PieceColor::White,SPRITE_DIRECTORY + "Queen_W.png"},
        {ChessPiece::PieceColor::Black,SPRITE_DIRECTORY + "Queen_B.png"}
};
const int Queen::QUEEN_POINT_VALUE = 9;

Queen::Queen(ChessPiece::PieceColor color):ChessPiece(color){
    std::lock_guard<std::mutex> fileLock(Queen::SpriteMutex);
    auto pathResult = SPRITE_MAP.find(color);
    if(pathResult != SPRITE_MAP.end()){
        sprite = wxImage(pathResult->second);
    }
    else{
        throw std::invalid_argument("That is not a valid color");
    }
}

Queen::~Queen() = default;

bool Queen::isMoveValid(){
    //Temporary value
    return false;
}

int Queen::getPointValue(){
    return QUEEN_POINT_VALUE;
}

wxImage Queen::getSprite(){
    return sprite;
}