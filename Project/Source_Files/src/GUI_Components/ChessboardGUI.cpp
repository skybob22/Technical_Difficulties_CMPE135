#include "ChessboardGUI.h"
#include "ChessTypes.h"
#include "ChessPiece.h"
#include "GameManager.h"

/**
 * @brief Creates a chessboard gui
 * @param parent The window frame that the chessboard is inside
 */
ChessboardGUI::ChessboardGUI(wxFrame* parent,GameManager* gameManager):wxPanel(parent,wxID_ANY),gameManager(gameManager),whiteColor(wxColour(0xFFFFFF)),blackColor(wxColour(0x606060)){
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
    wxGridSizer* grid = new wxGridSizer(GameManager::getBoardHeight(),GameManager::getBoardWidth(),0,0);

    //Initialize boardSquares to be a WIDTH x HEIGHT grid of nullptr
    boardSquares = std::vector<std::vector<wxButton*>>(GameManager::getBoardWidth(),std::vector<wxButton*>(GameManager::getBoardHeight(),nullptr));
    //Fill board squares with buttons
    for(unsigned int row=0;row < GameManager::getBoardHeight();row++){
        for(unsigned int col=0;col<GameManager::getBoardWidth();col++){
            boardSquares[row][col] = new wxButton(this,row*100+col);
            wxButton* currentSquare = boardSquares[row][col];

            wxColor squareColor = ((row+col)%2==0)?whiteColor:blackColor;
            currentSquare->SetBackgroundColour(squareColor);
            currentSquare->SetMinSize(wxSize(50,50)); //TODO: Why doesn't SetMinSize have any effect?
            grid->Add(currentSquare,1,wxEXPAND | wxALL);
        }
    }

    grid->Layout();
    this->SetSizer(grid);

    //Register self as observer
    gameManager->registerObserver(this);

    //Render the board
    update();
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
    update();
}

/**
 * @brief Redraws the board based on updated conditions
 */
void ChessboardGUI::update(){
    //Recolor squares and move/resize sprites as needed
    std::vector<std::vector<const ChessPiece*>> boardState = gameManager->getBoardState();

    for(unsigned int row=0;row<GameManager::getBoardHeight();row++){
        for(unsigned int col=0;col<GameManager::getBoardWidth();col++){
            wxButton* currentSquare = boardSquares[row][col];

            //Color for chessboard squares
            wxColor squareColor = ((row+col)%2==0)?whiteColor:blackColor;
            currentSquare->SetBackgroundColour(squareColor);

            //Add sprites to board where pieces exist
            if(boardState[row][col] != nullptr){
                int new_width = (currentSquare->m_width > 0)?currentSquare->m_width:1;
                int new_height = (currentSquare->m_height > 0)?currentSquare->m_height:1;
                currentSquare->SetBitmap(wxBitmap(boardState[row][col]->getSprite().Scale(new_width,new_height)));
            }
        }
    }
}