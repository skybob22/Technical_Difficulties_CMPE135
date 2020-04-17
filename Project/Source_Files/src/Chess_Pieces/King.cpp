#include "King.h"
#include <iostream>

std::mutex King::SpriteMutex;

const std::unordered_map<ChessPiece::PieceColor,std::string> King::SPRITE_MAP = {
        {ChessPiece::PieceColor::White,SPRITE_DIRECTORY + "King_W.png"},
        {ChessPiece::PieceColor::Black,SPRITE_DIRECTORY + "King_B.png"}
};
const int King::KING_POINT_VALUE = 0;

King::King(ChessPiece::PieceColor color):ChessPiece(color){
    std::lock_guard<std::mutex> fileLock(King::SpriteMutex);
    auto pathResult = SPRITE_MAP.find(color);
    if(pathResult != SPRITE_MAP.end()){
        sprite = wxImage(pathResult->second);
    }
    else{
        throw std::invalid_argument("That is not a valid color");
    }
}

King::~King() = default;

bool King::isMoveValid(){
    //Temporary value
    return false;
}

int King::getPointValue(){
    return KING_POINT_VALUE;
}

wxImage King::getSprite(){
    return sprite;
}