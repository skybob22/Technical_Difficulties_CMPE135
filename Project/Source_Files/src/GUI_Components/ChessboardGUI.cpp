#include "ChessboardGUI.h"
#include "ChessTypes.h"
#include "ChessPiece.h"

//Size of the chessboard
const unsigned int ChessboardGUI::BOARD_WIDTH = 8;
const unsigned int ChessboardGUI::BOARD_HEIGHT = 8;

/**
 * @brief Creates a chessboard gui
 * @param parent The window frame that the chessboard is inside
 */
ChessboardGUI::ChessboardGUI(wxFrame* parent):wxPanel(parent,wxID_ANY),whiteColor(wxColour(0xFFFFFF)),blackColor(wxColour(0x606060)){
    OnInit();
}

/**
 * @brief Destroys a chessboard object
 */
ChessboardGUI::~ChessboardGUI() = default;

/**
 * @brief Initializes the chessboard
 */
void ChessboardGUI::OnInit(){
    //Create Grid
    wxGridSizer* grid = new wxGridSizer(BOARD_HEIGHT,BOARD_WIDTH,0,0);

    //Initialize boardSquares to be a WIDTH x HEIGHT grid of nullptr
    boardSquares = std::vector<std::vector<wxButton*>>(BOARD_WIDTH,std::vector<wxButton*>(BOARD_HEIGHT,nullptr));
    //Fill board squares with buttons
    for(unsigned int row=0;row < BOARD_HEIGHT;row++){
        for(unsigned int col=0;col<BOARD_WIDTH;col++){
            boardSquares[row][col] = new wxButton(this,row*100+col);
            wxButton* currentSquare = boardSquares[row][col];

            wxColor squareColor = ((row+col)%2==0)?whiteColor:blackColor;
            currentSquare->SetBackgroundColour(squareColor);
            currentSquare->SetMinSize(wxSize(50,50)); //TODO: Why doesn't SetMinSize have any effect?
            grid->Add(currentSquare,1,wxEXPAND | wxALL);
        }
    }

    //Set up initial pieces
    chessPieces = std::vector<std::vector<ChessPiece*>>(BOARD_WIDTH,std::vector<ChessPiece*>(BOARD_HEIGHT,nullptr));

    grid->Layout();
    this->SetSizer(grid);

    //Render the board
    ResetBoard();
}

/**
 * @brief Used to change the color of squares on the chessboard
 * @param type The type of square you want to change the color of (White or Black)
 * @param newColor The new color to make the squares
 */
void ChessboardGUI::setColor(ChessColor type, const wxColour& newColor){
    switch(type){
        case White:
            whiteColor = newColor;
            break;
        case Black:
            blackColor = newColor;
            break;
    }
    Redraw();
}

/**
 * @brief Resets the board to a new game of chess
 */
void ChessboardGUI::ResetBoard() {
    for(unsigned int row=0;row < BOARD_HEIGHT;row++){
        for(unsigned int col=0;col<BOARD_WIDTH;col++){
            if(chessPieces[row][col] != nullptr){
                delete chessPieces[row][col];
                chessPieces[row][col] = nullptr;
            }

            //TODO: Find more elegant way of doing this
            //Black Pieces
            ChessColor playerColor = (row > 3)?White:Black;
            if(row == 0 || row == 7){
                if(col == 0 || col == 7){
                    //Rooks
                    chessPieces[row][col] = ChessPiece::createChessPiece(playerColor,Rook,BoardCoordinate(row,col));
                }
                else if(col == 1 || col == 6){
                    //Knights
                    chessPieces[row][col] = ChessPiece::createChessPiece(playerColor,Knight,BoardCoordinate(row,col));
                }
                else if(col == 2 || col == 5){
                    //Bishops
                    chessPieces[row][col] = ChessPiece::createChessPiece(playerColor,Bishop,BoardCoordinate(row,col));
                }
                else if(col == 3){
                    //Queen
                    chessPieces[row][col] = ChessPiece::createChessPiece(playerColor,Queen,BoardCoordinate(row,col));
                }
                else if(col == 4){
                    //King
                    chessPieces[row][col] = ChessPiece::createChessPiece(playerColor,King,BoardCoordinate(row,col));
                }
            }
            else if (row == 1 || row == 6){
                //Pawns
                chessPieces[row][col] = ChessPiece::createChessPiece(playerColor,Pawn,BoardCoordinate(row,col));
            }
        }
    }
    Redraw();
}

/**
 * @brief Redraws the board based on updated conditions
 */
void ChessboardGUI::Redraw(){
    //Recolor squares and move/resize sprites as needed
    for(unsigned int row=0;row<BOARD_HEIGHT;row++){
        for(unsigned int col=0;col<BOARD_WIDTH;col++){
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
}