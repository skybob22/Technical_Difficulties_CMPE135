#include "Knight.h"
#include <iostream>

std::mutex Knight::SpriteMutex;

const std::unordered_map<ChessPiece::PieceColor,std::string> Knight::SPRITE_MAP = {
        {ChessPiece::PieceColor::White,SPRITE_DIRECTORY + "Knight_W.png"},
        {ChessPiece::PieceColor::Black,SPRITE_DIRECTORY + "Knight_B.png"}
};
const int Knight::KNIGHT_POINT_VALUE = 3;

Knight::Knight(ChessPiece::PieceColor color):ChessPiece(color){
    std::lock_guard<std::mutex> fileLock(Knight::SpriteMutex);
    auto pathResult = SPRITE_MAP.find(color);
    if(pathResult != SPRITE_MAP.end()){
        sprite = wxImage(pathResult->second);
    }
    else{
        throw std::invalid_argument("That is not a valid color");
    }
}

Knight::~Knight() = default;

bool Knight::isMoveValid(){
    //Temporary value
    return false;
}

int Knight::getPointValue(){
    return KNIGHT_POINT_VALUE;
}

wxImage Knight::getSprite(){
    return sprite;
}