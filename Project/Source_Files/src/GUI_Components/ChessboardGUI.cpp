#include "ChessboardGUI.h"

//Chess Pieces TODO: Find some way to include these all at once, or move elsewhere
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

const unsigned int ChessboardGUI::BOARD_WIDTH = 8;
const unsigned int ChessboardGUI::BOARD_HEIGHT = 8;

ChessboardGUI::ChessboardGUI(wxFrame* parent):wxPanel(parent,wxID_ANY),whiteColor(wxColour(0xFFFFFF)),blackColor(wxColour(0x606060)){
    OnInit();
}

ChessboardGUI::~ChessboardGUI() = default;

void ChessboardGUI::OnInit(){
    //Create Grid
    wxGridSizer* grid = new wxGridSizer(BOARD_HEIGHT,BOARD_WIDTH,0,0);

    //Initialize boardSquares to be a WIDTH x HEIGHT grid of nullptr
    boardSquares = std::vector<std::vector<wxButton*>>(BOARD_WIDTH,std::vector<wxButton*>(BOARD_HEIGHT,nullptr));
    //Fill board squares with buttons
    for (unsigned int row=0;row < BOARD_HEIGHT;row++){
        for (unsigned int col=0;col<BOARD_WIDTH;col++){
            boardSquares[row][col] = new wxButton(this,row*100+col);
            wxColor squareColor = ((row+col)%2==0)?whiteColor:blackColor;
            boardSquares[row][col]->SetBackgroundColour(squareColor);
            //TODO: Why doesn't SetMinSize have any effect?
            boardSquares[row][col]->SetMinSize(wxSize(50,50));
            grid->Add(boardSquares[row][col],1,wxEXPAND | wxALL);
        }
    }

    //Set up initial pieces
    chessPieces = std::vector<std::vector<ChessPiece*>>(BOARD_WIDTH,std::vector<ChessPiece*>(BOARD_HEIGHT,nullptr));

    grid->Layout();
    this->SetSizer(grid);

    //Render the board
    ResetBoard();
}

void ChessboardGUI::setColor(ChessboardGUI::squareType type, wxColour newColor){
    switch(type){
        case White:{
            whiteColor = newColor;
            break;
        }
        case Black:{
            blackColor = newColor;
            break;
        }
    }
    Redraw();
}

void ChessboardGUI::ResetBoard() {
    for (unsigned int row=0;row < BOARD_HEIGHT;row++){
        for (unsigned int col=0;col<BOARD_WIDTH;col++){
            if (chessPieces[row][col] != nullptr){
                delete chessPieces[row][col];
                chessPieces[row][col] = nullptr;
            }

            //Black Pieces
            if(row == 0){
                if(col == 0 || col == 7){
                    //Rooks
                    chessPieces[row][col] = new Rook(ChessPiece::PieceColor::Black);
                }
                else if(col == 1 || col == 6){
                    //Knights
                    chessPieces[row][col] = new Knight(ChessPiece::PieceColor::Black);
                }
                else if(col == 2 || col == 5){
                    //Bishops
                    chessPieces[row][col] = new Bishop(ChessPiece::PieceColor::Black);
                }
                else if(col == 3){
                    //Queen
                    chessPieces[row][col] = new Queen(ChessPiece::PieceColor::Black);
                }
                else if(col == 4){
                    //King
                    chessPieces[row][col] = new King(ChessPiece::PieceColor::Black);
                }
            }
            else if(row == 1){
                //Pawns
                chessPieces[row][col] = new Pawn(ChessPiece::PieceColor::Black);
            }

            //White Pieces
            else if(row == 6){
                //Pawns
                chessPieces[row][col] = new Pawn(ChessPiece::PieceColor::White);
            }
            else if(row == 7){
                if(col == 0 || col == 7){
                    //Rooks
                    chessPieces[row][col] = new Rook(ChessPiece::PieceColor::White);
                }
                else if(col == 1 || col == 6){
                    //Knights
                    chessPieces[row][col] = new Knight(ChessPiece::PieceColor::White);
                }
                else if(col == 2 || col == 5){
                    //Bishops
                    chessPieces[row][col] = new Bishop(ChessPiece::PieceColor::White);
                }
                else if (col == 3){
                    //Queen
                    chessPieces[row][col] = new Queen(ChessPiece::PieceColor::White);
                }
                else if (col == 4){
                    //King
                    chessPieces[row][col] = new King(ChessPiece::PieceColor::White);
                }
            }
        }
    }
    Redraw();
}

void ChessboardGUI::Redraw(){
    //Recolor squares
    for (unsigned int row=0;row < BOARD_HEIGHT;row++){
        for (unsigned int col=0;col<BOARD_WIDTH;col++){
            wxButton* currentSquare = boardSquares[row][col];
            wxColor squareColor = ((row+col)%2==0)?whiteColor:blackColor;
            currentSquare->SetBackgroundColour(squareColor);

            if(chessPieces[row][col] != nullptr){
                int new_width = (currentSquare->m_width > 0)?currentSquare->m_width:1;
                int new_height = (currentSquare->m_height > 0)?currentSquare->m_height:1;
                currentSquare->SetBitmap(wxBitmap(chessPieces[row][col]->getSprite().Scale(new_width,new_height)));
            }
        }
    }
    //TODO: Add drawing chess piece sprites
}