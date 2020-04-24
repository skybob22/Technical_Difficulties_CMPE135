#include "GameManager.h"

//Constants for defining the size of the board
const unsigned int GameManager::BOARD_HEIGHT = 8;
const unsigned int GameManager::BOARD_WIDTH = 8;

//Default white pieces to use
const std::vector<GameManager::PieceInfo> GameManager::DEFAULT_WHITE_PIECES = {

        PieceInfo(White,Pawn,BoardCoordinate(6,0)),
        PieceInfo(White,Pawn,BoardCoordinate(6,1)),
        PieceInfo(White,Pawn,BoardCoordinate(6,2)),
        PieceInfo(White,Pawn,BoardCoordinate(6,3)),
        PieceInfo(White,Pawn,BoardCoordinate(6,4)),
        PieceInfo(White,Pawn,BoardCoordinate(6,5)),
        PieceInfo(White,Pawn,BoardCoordinate(6,6)),
        PieceInfo(White,Pawn,BoardCoordinate(6,7)),
        PieceInfo(White,Rook,BoardCoordinate(7,0)),
        PieceInfo(White,Knight,BoardCoordinate(7,1)),
        PieceInfo(White,Bishop,BoardCoordinate(7,2)),
        PieceInfo(White,King,BoardCoordinate(7,3)),
        PieceInfo(White,Queen,BoardCoordinate(7,4)),
        PieceInfo(White,Bishop,BoardCoordinate(7,5)),
        PieceInfo(White,Knight,BoardCoordinate(7,6)),
        PieceInfo(White,Rook,BoardCoordinate(7,7))
};

//Default black pieces to use
const std::vector<GameManager::PieceInfo> GameManager::DEFAULT_BLACK_PIECES = {
        PieceInfo(Black,Rook,BoardCoordinate(0,0)),
        PieceInfo(Black,Knight,BoardCoordinate(0,1)),
        PieceInfo(Black,Bishop,BoardCoordinate(0,2)),
        PieceInfo(Black,King,BoardCoordinate(0,3)),
        PieceInfo(Black,Queen,BoardCoordinate(0,4)),
        PieceInfo(Black,Bishop,BoardCoordinate(0,5)),
        PieceInfo(Black,Knight,BoardCoordinate(0,6)),
        PieceInfo(Black,Rook,BoardCoordinate(0,7)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,0)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,1)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,2)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,3)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,4)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,5)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,6)),
        PieceInfo(Black,Pawn,BoardCoordinate(1,7))
};

/**
 * @brief Gets the height of the board
 * @return The board height
 */
unsigned int GameManager::getBoardHeight(){
    return BOARD_HEIGHT;
}

/**
 * @brief Gets the width of the board
 * @return The board width
 */
unsigned int GameManager::getBoardWidth(){
    return BOARD_WIDTH;
}

/**
 * @brief Constructs a new GameManager object
 */
GameManager::GameManager():gameStarted(false){
    playerTurn = White;
}

/**
 * @brief Copy constructor for GameManager, DONT USE
 * @param other GameManager to make a copy of
 */
GameManager::GameManager(const GameManager& other) =  default;

/**
 * @brief Destroys a GameManager object
 */
GameManager::~GameManager(){
    while(!moveHistory.empty()){
        ChessMove move = moveHistory.top();
        moveHistory.pop();
        delete move.pieceTaken; //Piece is not in normal pieces list, so must delete it here
    }
}

/**
 * @brief Sets the board to the default starting state and starts a new game
 */
void GameManager::newGame(){
    whitePieces.clear();
    for(PieceInfo piece : DEFAULT_WHITE_PIECES){
        whitePieces.insert(new ChessPiece(piece.color,piece.type,piece.pos));
    }
    blackPieces.clear();
    for(PieceInfo piece : DEFAULT_BLACK_PIECES){
        blackPieces.insert(new ChessPiece(piece.color,piece.type,piece.pos));
    }

    gameStarted = true;
    playerTurn = White;

    updateObservers();
}

/**
 * @brief Attempts to move a piece, and returns whether the peice was moved
 * @param start The starting location of the piece
 * @param dest The desired destination of the piece
 * @return Whether the move was successful or not (returns false if invalid move)
 */
bool GameManager::movePiece(BoardCoordinate start, BoardCoordinate dest){
    //Check if move is valid, if so then perform move

    //Check if player's king is in check, if so undo move and return false

    //Temporary return value
    updateObservers();
    return false;
}

/**
 * @brief Undoes the last move
 */
void GameManager::undoMove(){
    if(!moveHistory.empty()) {
        //Revert board state to previous state

        moveHistory.pop();
        updateObservers();
    }
}

/**
 * @brief checks to see if the specified piece (king) is in check
 * @param color The color of the king that we wish to check
 * @return Whether the king is in check or not
 */
bool GameManager::isKingInCheck(ChessColor color){
    //Temporary return value
    return false;
}

/**
 * @brief checks to see if the specified piece (king) is in checkmate
 * @param color The color of the king that we wish to check
 * @return Whether the king is in checkmate or not
 */
bool GameManager::isKingInCheckmate(ChessColor color){
    //Temporary return value
    return false;
}

/**
 * @brief Gets the current state of the board (used for rendering)
 * @return A vector containing pointers representing where on the board pieces are
 */
std::vector<std::vector<const ChessPiece*>> GameManager::getBoardState() const{
    //Create board vector
    auto boardState = std::vector<std::vector<const ChessPiece*>>(BOARD_WIDTH,std::vector<const ChessPiece*>(BOARD_HEIGHT,nullptr));

    for(ChessPiece* piece : whitePieces){
        boardState[piece->getPosition().y][piece->getPosition().x] = piece;
    }
    for(ChessPiece* piece : blackPieces){
        boardState[piece->getPosition().y][piece->getPosition().x] = piece;
    }

    return boardState;
}

/**
 * @brief Registers an observer to be notified when the board state is changed
 * @param observer A pointer to the observer to be added
 */
void GameManager::registerObserver(Observer* observer){
    observers.insert(observer);
}

/**
 * @brief Removes an observer from the list of observers
 * @param observer A pointer to the observer to be removed
 */
void GameManager::removeObserver(Observer* observer){
    observers.erase(observer);
}

/**
 * @brief Updates all the observers by calling their update() function
 */
void GameManager::updateObservers(){
    for(auto observer : observers){
        observer->update();
    }
}