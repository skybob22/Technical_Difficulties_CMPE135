#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Subject.h"
#include "ChessTypes.h"
#include "ChessPiece.h"

#include <unordered_set>
#include <stack>
#include <list>

class GameManager : public Subject{
public:
    GameManager();
    ~GameManager();
    GameManager(const GameManager& other) = delete;

    void newGame();

    //Game interaction
    ChessColor getPlayerTurn() const;
    bool movePiece(BoardCoordinate start,BoardCoordinate dest);
    void undoMove();
    std::vector<std::vector<ChessPiece*>> getBoardState() const;

    bool isKingInCheck(ChessColor color) const;
    bool isKingInCheckmate(ChessColor color) const;

    //Subject Functionality
    void registerObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;

    //Board information
    static unsigned int getBoardHeight();
    static unsigned int getBoardWidth();

private:
    //Player turn
    bool gameStarted;
    ChessColor playerTurn;

    //Keeping track of moves
    struct ChessMove{
        BoardCoordinate start;
        BoardCoordinate dest;
        ChessPiece* pieceTaken;
        ChessMove(BoardCoordinate start,BoardCoordinate dest,ChessPiece* piece):
            start(start),dest(dest),pieceTaken(piece){};
    };
    std::stack<ChessMove,std::list<ChessMove>> moveHistory;
    void forceMove(BoardCoordinate start,BoardCoordinate dest);
    bool silentMode; //Used so functions can be internally called without updating observers

    //Keep track of pieces
    //TODO: Try and figure out better data structure
    std::unordered_set<ChessPiece*> whitePieces,blackPieces;
    std::vector<std::vector<ChessPiece*>> boardState;
    ChessPiece* WhiteKing;
    ChessPiece* BlackKing;

    //Subject Functionality
    void updateObservers() override;
    std::unordered_set<Observer*> observers;


    //Constants
    const static unsigned int BOARD_HEIGHT,BOARD_WIDTH;

    //Default starting state
    //TODO: Figure out if there's a better way to store this info?
    struct PieceInfo{
        //Used as placeholder info since ChessPiece cannot be instantiated statically
        ChessColor color;
        PieceType type;
        BoardCoordinate pos;
        PieceInfo(ChessColor color,PieceType type,BoardCoordinate pos):color(color),type(type),pos(pos){};
    };
    const static std::vector<PieceInfo> DEFAULT_WHITE_PIECES,DEFAULT_BLACK_PIECES;
};

#endif