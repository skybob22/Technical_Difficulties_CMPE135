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
        PieceInfo(White,Queen,BoardCoordinate(7,3)),
        PieceInfo(White,King,BoardCoordinate(7,4)),
        PieceInfo(White,Bishop,BoardCoordinate(7,5)),
        PieceInfo(White,Knight,BoardCoordinate(7,6)),
        PieceInfo(White,Rook,BoardCoordinate(7,7))
};

//Default black pieces to use
const std::vector<GameManager::PieceInfo> GameManager::DEFAULT_BLACK_PIECES = {
        PieceInfo(Black,Rook,BoardCoordinate(0,0)),
        PieceInfo(Black,Knight,BoardCoordinate(0,1)),
        PieceInfo(Black,Bishop,BoardCoordinate(0,2)),
        PieceInfo(Black,Queen,BoardCoordinate(0,3)),
        PieceInfo(Black,King,BoardCoordinate(0,4)),
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
GameManager::GameManager():gameStarted(false),silentMode(false){
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

    //Create new board state vector
    boardState = std::vector<std::vector<ChessPiece*>>(BOARD_HEIGHT,std::vector<ChessPiece*>(BOARD_WIDTH,nullptr));

    //Delete all the old pieces and make new ones
    std::set<ChessColor> colors = {White,Black};
    for(ChessColor color : colors){
        std::unordered_set<ChessPiece*>& pieceSet = (color==White?whitePieces:blackPieces);
        for(auto piece : pieceSet){
            delete piece;
        }
        pieceSet.clear();

        for(PieceInfo piece : (color == White?DEFAULT_WHITE_PIECES:DEFAULT_BLACK_PIECES)){
            ChessPiece* pieceToInsert = new ChessPiece(piece.color,piece.type,piece.pos);
            pieceSet.insert(pieceToInsert);
            boardState[piece.pos.y][piece.pos.x] = pieceToInsert;

            //Keep track of the king so we can easily find it for checking check/checkmate
            if(piece.type == King){
                (color == White?WhiteKing:BlackKing) = pieceToInsert;
            }
        }
    }

    gameStarted = true;
    playerTurn = White;
    if(!silentMode) {
        updateObservers();
    }
}

/**
 * @brief Ends a game
 */
void GameManager::endGame(){
    gameStarted = false;
}

/**
 * @brief Gets whether a game is in progress or not
 * @return If a game has been started
 */
bool GameManager::isGameInProgress() const{
    return gameStarted;
}

/**
 * @brief Gets which player's turn it is
 * @return Which player's turn it is (White or Black)
 */
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

    //Perform the move, we have already ensured move is valid and correct player turn
    forceMove(start,dest);

    //Check if player's king is in check, if so undo move and return false
    if(isKingInCheck()){
        undoMove();
        return false;
    }

    //Change the turn to other color
    playerTurn = !playerTurn;
    if(!silentMode) {
        updateObservers();
    }
    return true;
}

/**
 * @brief Forcibly moves a piece without checking if the move is valid or not, and ignores turn color
 * @param start Where the piece is moving from
 * @param dest Where the piece is moving to
 */
void GameManager::forceMove(BoardCoordinate start,BoardCoordinate dest){
    //Perform the move
    ChessPiece* pieceToMove = boardState[start.y][start.x];
    if(pieceToMove == nullptr){
        //Only validity check in function. If piece is nullptr, nothing to move
        return;
    }
    moveHistory.emplace(start,dest,boardState[dest.y][dest.x]);
    if(boardState[dest.y][dest.x] != nullptr){
        //Remove the piece from the appropriate set
        std::unordered_set<ChessPiece*>& pieceSet = (boardState[dest.y][dest.x]->getColor()==White?whitePieces:blackPieces);
        pieceSet.erase(boardState[dest.y][dest.x]);
    }
    pieceToMove->move(dest);
    boardState[dest.y][dest.x] = pieceToMove;
    boardState[start.y][start.x] = nullptr;
}

/**
 * @brief Undoes the last move
 */
bool GameManager::undoMove(){
    if(moveHistory.empty()){
        return false;
    }

    if(moveHistory.top().start == moveHistory.top().dest){
        //Special case when pawn reaches end and is promoted, need to undo last 2 moves instead of last 1
        ChessMove promotion = moveHistory.top();
        BoardCoordinate pos = promotion.start;
        ChessPiece* pieceToRemove = boardState[pos.y][pos.x];
        std::unordered_set<ChessPiece*>& pieceSet = (pieceToRemove->getColor()==White?whitePieces:blackPieces);

        //Remove the old piece from the board
        pieceSet.erase(pieceToRemove);

        //Re-add the pawn to the board
        boardState[pos.y][pos.x] = promotion.pieceTaken;
        pieceSet.insert(promotion.pieceTaken);

        delete pieceToRemove;
        moveHistory.pop();
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
        std::unordered_set<ChessPiece*>& pieceSet = (lastMove.pieceTaken->getColor() == White?whitePieces:blackPieces);
        pieceSet.insert(lastMove.pieceTaken);
    }

    moveHistory.pop();
    gameStarted = true;
    if(!silentMode) {
        updateObservers();
    }
    return true;
}

/**
 * @brief Promotes a pawn to a different type of piece
 * @param pos The position of the pawn to promote
 * @param type The type of piece to turn the pawn into
 */
bool GameManager::promotePawn(BoardCoordinate pos, PieceType type){
    if(!MovementChecker::isPositionOnBoard(pos) || (pos.y != 0 && pos.y != BOARD_HEIGHT-1)){
        //Piece must be in top or bottom row
        return false;
    }

    ChessPiece* pieceToReplace = boardState[pos.y][pos.x];
    if(pieceToReplace == nullptr || pieceToReplace->getPieceType() != Pawn){
        //Piece must be a pawn
        return false;
    }

    ChessColor pieceColor = pieceToReplace->getColor();
    std::unordered_set<ChessPiece*>& pieceSet = (pieceColor==White?whitePieces:blackPieces);

    pieceSet.erase(pieceToReplace);
    moveHistory.emplace(pos,pos,pieceToReplace);
    ChessPiece* newPiece = new ChessPiece(pieceColor,type,pos);
    boardState[pos.y][pos.x] = newPiece;
    pieceSet.insert(newPiece);
    return true;
}

/**
 * @brief checks to see if the specified piece (king) is in check
 * @param color The color of the king that we wish to check
 * @return Whether the king is in check or not
 */
bool GameManager::isKingInCheck() const{
    if(!gameStarted){
        //Cannot have check/checkmate if no game running
        return false;
    }

    for(auto piece : (playerTurn == White?blackPieces:whitePieces)){
        if(piece->isMoveValid((playerTurn == White?WhiteKing:BlackKing)->getPosition(),boardState)){
            //If any piece puts the king in check, we don't need to continue checking
            return true;
        }
    }
    //If none of the pieces puts the king in check, then king is not in check
    return false;
}

/**
 * @brief checks to see if the specified piece (king) is in checkmate
 * @param color The color of the king that we wish to check
 * @return Whether the king is in checkmate or not
 */
bool GameManager::isKingInCheckmate() const{
    /*
     * Technically speaking, this function is not const as it modifies the internal state,
     * However it guarantees that it will return the state to the original state before returning, so it is still declared const
     */

    if(!isKingInCheck()){
        //Checking for checkmate is expensive, don't do it if the king isn't in check
        return false;
    }

    //Stalemate means player cannot move any pieces. Checkmate is basically the same as stalemate + the king is in check
    return isStalemate();
}

/**
 * @brief Checks to see if the game is in stalemate
 * @return Whether the game is in stalemate
 */
bool GameManager::isStalemate() const{
    const_cast<GameManager*>(this)->silentMode = true;
    for(auto piece : (playerTurn == White?whitePieces:blackPieces)){
        for(auto spot : piece->getValidMoves(boardState)){
            //Try every possible valid move for pieces of that color
            const_cast<GameManager*>(this)->forceMove(piece->getPosition(),spot);
            if(!isKingInCheck()){
                //If any single move takes the king out of check, then there is a valid move
                const_cast<GameManager*>(this)->undoMove();
                const_cast<GameManager*>(this)->silentMode = false;
                return false;
            }
            else{
                const_cast<GameManager*>(this)->undoMove();
            }
        }
    }
    //If no possible moves take do not leave the king in check, then there is stalemate
    const_cast<GameManager*>(this)->silentMode = false;
    return true;
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