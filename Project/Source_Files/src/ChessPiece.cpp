#include "ChessPiece.h"

//Location where the sprite images are stored
const std::string ChessPiece::SPRITE_DIRECTORY = "./Sprites/PNG/";

//Stores specific path to sprites based on color and type of piece
const std::unordered_map<PieceType,std::unordered_map<ChessColor,std::string>> ChessPiece::SPRITE_PATH_MAP = {
        {King,{
            {White,SPRITE_DIRECTORY + "King_W.png"},
            {Black,SPRITE_DIRECTORY + "King_B.png"}
        }},
        {Queen,{
            {White,SPRITE_DIRECTORY + "Queen_W.png"},
            {Black,SPRITE_DIRECTORY + "Queen_B.png"}
         }},
        {Bishop,{
            {White,SPRITE_DIRECTORY + "Bishop_W.png"},
            {Black,SPRITE_DIRECTORY + "Bishop_B.png"}
         }},
        {Knight,{
            {White,SPRITE_DIRECTORY + "Knight_W.png"},
            {Black,SPRITE_DIRECTORY + "Knight_B.png"}
         }},
        {Rook,{
            {White,SPRITE_DIRECTORY + "Rook_W.png"},
            {Black,SPRITE_DIRECTORY + "Rook_B.png"}
         }},
        {Pawn,{
            {White,SPRITE_DIRECTORY + "Pawn_W.png"},
            {Black,SPRITE_DIRECTORY + "Pawn_B.png"}
         }}
};

//The point values of the different types of pieces
const std::unordered_map<PieceType,int> ChessPiece::POINT_VALUE_MAP = {
        {King,0},
        {Queen,9},
        {Bishop,3},
        {Knight,3},
        {Rook,5},
        {Pawn,1}
};

/**
 * Creates a new chess piece
 * @param color The color (White or Black)
 * @param type The type of piece (King, Queen, etc.)
 * @param position The current location of the piece on the board
 */
ChessPiece::ChessPiece(ChessColor color,PieceType type,BoardCoordinate position):position(position),color(color),type(type){
    moveChecker = MovementChecker::createMovementChecker(type);

    auto typeSearch = SPRITE_PATH_MAP.find(type);
    if(typeSearch != SPRITE_PATH_MAP.end()){
        auto colorSearch = typeSearch->second.find(color);
        if(colorSearch != typeSearch->second.end()){
            sprite = wxImage(colorSearch->second);
        }
        else{
            throw std::invalid_argument("Invalid color passed to constructor");
        }
    }
    else{
        throw std::invalid_argument("Invalid piece type passed to constructor");
    }
}

/**
 * @brief Copy constructor for chess piece, constructs a ChessPiece by referencing another
 * @param other
 */
ChessPiece::ChessPiece(const ChessPiece& other):position(other.position),color(other.color),type(other.type),sprite(other.sprite){
    moveChecker = MovementChecker::createMovementChecker(other.type);
}

/**
 * @brief Destroys a chess piece
 */
ChessPiece::~ChessPiece(){
    delete moveChecker;
    moveChecker = nullptr;
}

/**
 * @brief Gets the color of the chess peice
 * @return The color of the chess piece (White or Black)
 */
ChessColor ChessPiece::getColor() const{
    return color;
}

/**
 * @brief Gets the type of chess piece
 * @return The type of piece (King, Queen, etc.)
 */
PieceType ChessPiece::getPieceType() const{
    return type;
}

/**
 * @brief Gets the sprite representing the peice, used for drawing the GUI
 * @return A wxImage with the appropriate sprite
 */
wxImage ChessPiece::getSprite() const{
    return sprite;
}

/**
 * @brief Checks to see if it is valid to move the piece to the specified location
 * @param pos The location you want to move the piece to
 * @param boardState The current board state (locations of all the pieces)
 * @return Whether the move is valid or not
 */
bool ChessPiece::isMoveValid(BoardCoordinate pos,const std::vector<std::vector<ChessPiece*>>& boardState) const{
    return moveChecker->isMoveValid(position,pos,boardState);
}

/**
 * @Brief Moves the piece elsewhere on the board and updates it's coordinates
 * @param pos The desired position to move to
 */
void ChessPiece::move(BoardCoordinate pos){
    position = pos;
}

/**
 * @brief Gets the number of points a piece is worth
 * @return The point value of the piece
 */
int ChessPiece::getPointValue() const{
    auto pointSearchResult = POINT_VALUE_MAP.find(type);
    if(pointSearchResult != POINT_VALUE_MAP.end()){
        return pointSearchResult->second;
    }
    else{
        return 0;
    }
}

/**
 * @brief Gets the current coordinates of the chess piece
 * @return The current position of the chess piece
 */
BoardCoordinate ChessPiece::getPosition() const{
    return position;
}