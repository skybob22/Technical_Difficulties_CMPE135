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
    boardState = std::vector<std::vector<ChessPiece*>>(BOARD_HEIGHT,std::vector<ChessPiece*>(BOARD_WIDTH,nullptr));
    playerTurn = White;
}

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
    while(!moveHistory.empty()){
        ChessMove move = moveHistory.top();
        moveHistory.pop();
        delete move.pieceTaken; //Piece is not in normal pieces list, so must delete it here
    }

    boardState = std::vector<std::vector<ChessPiece*>>(BOARD_HEIGHT,std::vector<ChessPiece*>(BOARD_WIDTH,nullptr));

    for(auto it : whitePieces){
        delete it;
    }
    whitePieces.clear();
    for(PieceInfo piece : DEFAULT_WHITE_PIECES){
        ChessPiece* pieceToInsert = new ChessPiece(piece.color,piece.type,piece.pos);
        boardState[piece.pos.y][piece.pos.x] = pieceToInsert;
        whitePieces.insert(pieceToInsert);

        //Keeps track of the king so we can easily find it for checking check/checkmate
        if(piece.type == King){
            WhiteKing = pieceToInsert;
        }
    }

    for(auto it : blackPieces){
        delete it;
    }
    blackPieces.clear();
    for(PieceInfo piece : DEFAULT_BLACK_PIECES){
        ChessPiece* pieceToInsert = new ChessPiece(piece.color,piece.type,piece.pos);
        boardState[piece.pos.y][piece.pos.x] = pieceToInsert;
        blackPieces.insert(pieceToInsert);

        //Keeps track of the king so we can easily find it for checking check/checkmate
        if(piece.type == King){
            BlackKing = pieceToInsert;
        }
    }

    gameStarted = true;
    playerTurn = White;

    updateObservers();
}

ChessColor GameManager::getPlayerTurn() const{
    return playerTurn;
}

/**
 * @brief Attempts to move a piece, and returns whether the piece was moved
 * @param start The starting location of the piece
 * @param dest The desired destination of the piece
 * @return Whether the move was successful or not (returns false if invalid move)
 */
bool GameManager::movePiece(BoardCoordinate start, BoardCoordinate dest){
    if(!MovementChecker::isPositionOnBoard(dest)){
        return false;
    }

    ChessPiece* pieceToMove = boardState[start.y][start.x];
    if( pieceToMove == nullptr){
        return false;
    }
    else if( pieceToMove->getColor() != playerTurn){
        //Can only move player's own pieces
        return false;
    }

    //Check if move is valid, if so then perform move
    //TODO: Figure out how to pass this in.
    //Copying is expensive, and it will not let me convert vector<vector<ChessPiece*>> to vector<vector<const ChessPiece*>>
    if(!pieceToMove->isMoveValid(dest,boardState)){
        return false;
    }

    //Perform the move
    moveHistory.push(std::move(ChessMove(start,dest,boardState[dest.y][dest.x])));
    if(boardState[dest.y][dest.x] != nullptr){
        //Try and remove from both, and if it's not present then nothing will happen
        whitePieces.erase(boardState[dest.y][dest.x]);
        blackPieces.erase(boardState[dest.y][dest.x]);
    }
    pieceToMove->move(dest);
    boardState[dest.y][dest.x] = pieceToMove;
    boardState[start.y][start.x] = nullptr;

    //Check if player's king is in check, if so undo move and return false
    if(isKingInCheck(playerTurn)){
        undoMove();
        return false;
    }

    //Temporary return value
    playerTurn = (playerTurn==White)?Black:White; //Change the turn back to whoever made the last move
    updateObservers();
    return true;
}

/**
 * @brief Undoes the last move
 */
void GameManager::undoMove(){
    if(!moveHistory.empty()) {
        if(moveHistory.top().start == moveHistory.top().dest){
            //Special case when pawn reaches end and is promoted, need to undo last 2 moves instead of last 1
            //TODO: Implement undoing promotion

        }

        //Revert board state to previous state
        ChessMove lastMove = moveHistory.top();
        ChessPiece* movedPiece = boardState[lastMove.dest.y][lastMove.dest.x];

        //Move piece back to where it was, and put the taken piece (can be nullptr) where the piece moved to
        if(movedPiece != nullptr){
            movedPiece->move(lastMove.start);
            playerTurn = movedPiece->getColor();
        }
        boardState[lastMove.start.y][lastMove.start.x] = movedPiece; //Move the piece back to where it was before
        boardState[lastMove.dest.y][lastMove.dest.x] = lastMove.pieceTaken;

        if(lastMove.pieceTaken != nullptr){
            if(lastMove.pieceTaken->getColor() == White){
                //Insert into white pieces
                whitePieces.insert(lastMove.pieceTaken);
            }
            else{
                //Insert into black pieces
                blackPieces.insert(lastMove.pieceTaken);
            }
        }

        moveHistory.pop();
        updateObservers();
    }
}

/**
 * @brief checks to see if the specified piece (king) is in check
 * @param color The color of the king that we wish to check
 * @return Whether the king is in check or not
 */
bool GameManager::isKingInCheck(ChessColor color) const{
    if(color == White){
        for(auto it : blackPieces){
            if (it->isMoveValid(WhiteKing->getPosition(),boardState)){
                //If any black piece puts the white king in check, we don't need to continue checking
                return true;
            }
        }
        //If none of the black pieces puts the white king in check, then king is not in check
        return false;
    }
    else{
        for(auto it : whitePieces){
            if (it->isMoveValid(BlackKing->getPosition(),boardState)){
                //If any black piece puts the black king in check, we don't need to continue checking
                return true;
            }
        }
        //If none of the white pieces puts the black king in check, then king is not in check
        return false;
    }
}

/**
 * @brief checks to see if the specified piece (king) is in checkmate
 * @param color The color of the king that we wish to check
 * @return Whether the king is in checkmate or not
 */
bool GameManager::isKingInCheckmate(ChessColor color) const{
    //Temporary return value
    return false;
}

/**
 * @brief Gets the current state of the board (used for rendering)
 * @return A vector containing pointers representing where on the board pieces are
 */
std::vector<std::vector<ChessPiece*>> GameManager::getBoardState() const{
    //TODO: Figure out how to return this
    //Copying is expensive, and it will not let me convert vector<vector<ChessPiece*>> to vector<vector<const ChessPiece*>>
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