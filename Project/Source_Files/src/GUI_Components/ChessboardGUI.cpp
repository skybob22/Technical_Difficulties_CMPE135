#include "ChessboardGUI.h"
#include "ChessTypes.h"
#include "ChessPiece.h"
#include "GameManager.h"
#include <iostream>

/**
 * @brief Creates a chessboard gui
 * @param parent The window frame that the chessboard is inside
 */
ChessboardGUI::ChessboardGUI(wxFrame* parent,GameManager* gameManager):wxPanel(parent,wxID_ANY),gameManager(gameManager),whiteColor(wxColour(0xFFFFFF)),blackColor(wxColour(0x606060)),selectedSquare(-1,-1){
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
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* grid = new wxGridSizer(GameManager::getBoardHeight(),GameManager::getBoardWidth(),0,0);

    //Initialize boardSquares to be a WIDTH x HEIGHT grid of nullptr
    boardSquares = std::vector<std::vector<wxBitmapButton*>>(GameManager::getBoardWidth(),std::vector<wxBitmapButton*>(GameManager::getBoardHeight(),nullptr));
    //Fill board squares with buttons
    for(unsigned int row=0;row < GameManager::getBoardHeight();row++){
        for(unsigned int col=0;col<GameManager::getBoardWidth();col++){
            boardSquares[row][col] = new wxBitmapButton(this,row*100+col,wxNullBitmap);
            wxButton* currentSquare = boardSquares[row][col];
            currentSquare->Bind(wxEVT_BUTTON,&ChessboardGUI::ButtonClicked,this);

            wxColor squareColor = ((row+col)%2==0)?whiteColor:blackColor;
            currentSquare->SetBackgroundColour(squareColor);
            currentSquare->SetMinSize(wxSize(50,50)); //TODO: Why doesn't SetMinSize have any effect?
            grid->Add(currentSquare,1,wxEXPAND | wxALL);
        }
    }

    grid->Layout();
    sizer->Add(grid,1,wxEXPAND | wxALL);
    wxBoxSizer* gameInfoSizer = new wxBoxSizer(wxVERTICAL);

    //Text to show which player's turn it is
    wxBoxSizer* turnInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* turnLabel = new wxStaticText(this,wxID_ANY,"Player Turn:");
    playerTurn = new wxStaticText(this,wxID_ANY,"");
    turnInfoSizer->Add(turnLabel);
    turnInfoSizer->Add(playerTurn);
    turnInfoSizer->Layout();

    gameInfoSizer->Add(turnInfoSizer);
    gameInfoSizer->Layout();

    sizer->Add(gameInfoSizer);
    sizer->Layout();

    this->SetSizer(sizer);

    //Register self as observer
    gameManager->registerObserver(this);

    //Render the board
    Redraw();
}

void ChessboardGUI::ButtonClicked(wxCommandEvent& evt){
    if(selectedSquare.x < 0){
        selectedSquare.y = evt.GetId()/100;
        selectedSquare.x = evt.GetId()%10;
        Redraw();
        return;
    }

    if(selectedSquare.y == evt.GetId()/100 && selectedSquare.x == evt.GetId()%10){
        selectedSquare.x = -1;
        selectedSquare.y = -1;
        Redraw();
        return;
    }

    //Attempt to move the piece
    if(gameManager->movePiece(selectedSquare,BoardCoordinate(evt.GetId()/100,evt.GetId()%10))){
        selectedSquare.y = -1;
        selectedSquare.x = -1;
    }
    Redraw();

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
 * @brief Redraws the board based on updated conditions
 */
void ChessboardGUI::update(){
    //Redraw the board state
    Redraw();

    //Update information/create windows based on updated information
    //Update player's turn
    playerTurn->SetLabelText(wxString(toString(gameManager->getPlayerTurn())));

    //Notify player if king is in check or checkmate
    if(gameManager->isKingInCheck(White)){
        if(gameManager->isKingInCheckmate(White)){
            wxMessageBox(wxString::Format("White king is in checkmate\nGame Over"), "", wxOK, this);
        }
        else {
            wxMessageBox(wxString::Format("White king is in check"), "", wxOK, this);
        }
    }
    if(gameManager->isKingInCheck(Black)){
        if(gameManager->isKingInCheckmate(Black)){
            wxMessageBox(wxString::Format("Black king is in checkmate\nGame Over"), "", wxOK, this);
        }
        else {
            wxMessageBox(wxString::Format("Black king is in check"), "", wxOK, this);
        }
    }
}

/**
 * @brief Redraws the chessboard
 */
void ChessboardGUI::Redraw(){
    //Recolor squares and move/resize sprites as needed
    std::vector<std::vector<ChessPiece*>> boardState = gameManager->getBoardState();

    for(unsigned int row=0;row<boardState.size();row++){
        for(unsigned int col=0;col<boardState[row].size();col++){
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
            else{
                currentSquare->SetBitmap(wxBitmap());//Attempt to replace with empty bitmap
                currentSquare->SetBackgroundColour(wxColor(0xFF0000)); //Temporary color to indicate places with no pieces
            }
        }
    }

    //Highlight selected square
    if(selectedSquare.y >=0 && selectedSquare.y < static_cast<int>(GameManager::getBoardHeight()) && selectedSquare.x >= 0 && selectedSquare.x < static_cast<int>(GameManager::getBoardWidth())){
        boardSquares[selectedSquare.y][selectedSquare.x]->SetBackgroundColour(wxColor(0x00FF00));
    }
}