#include "ChessboardGUI.h"
#include "ChessTypes.h"
#include "ChessPiece.h"
#include "GameManager.h"

const std::string ChessboardGUI::SPRITE_DIRECTORY = "./Sprites/PNG/";

/**
 * @brief Creates a chessboard gui
 * @param parent The window frame that the chessboard is inside
 */
ChessboardGUI::ChessboardGUI(wxFrame* parent,GameManager* gameManager):wxPanel(parent,wxID_ANY),gameManager(gameManager),whiteColor(wxColour(0xFFFFFF)),blackColor(wxColour(0x606060)),transparentSquare(SPRITE_DIRECTORY + "Transparent.png"),selectedSquare(-1,-1){
    this->parent = parent;
    flip = false;
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

    //Create the menu for promoting pawns
    promotionMenu = new wxMenu;
    std::vector<std::pair<PieceType,std::string>> menu_pairs = {
            {Queen,"Queen"},
            {Bishop,"Bishop"},
            {Knight,"Knight"},
            {Rook,"Rook"},
    };
    for(auto it : menu_pairs){
        promotionMenu->Append(std::get<0>(it),std::get<1>(it));
    }
}

/**
 * @brief Called when a square on the chess board is clicked
 * @param evt The WX even generated
 */
void ChessboardGUI::ButtonClicked(wxCommandEvent& evt){
    if(!gameManager->isGameInProgress()){
        return;
    }

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

    //Calculate adjusted position, taking board flip into account
    int startY = static_cast<int>((flip&&gameManager->getPlayerTurn()==Black)?(GameManager::getBoardHeight()-1-selectedSquare.y):selectedSquare.y);
    int startX = static_cast<int>((flip&&gameManager->getPlayerTurn()==Black)?(GameManager::getBoardHeight()-1-selectedSquare.x):selectedSquare.x);
    int destY = static_cast<int>((flip&& gameManager->getPlayerTurn()==Black)?(GameManager::getBoardWidth()+-1-evt.GetId()/100):evt.GetId()/100);
    int destX = static_cast<int>((flip&& gameManager->getPlayerTurn()==Black)?(GameManager::getBoardWidth()-1-evt.GetId()%10):evt.GetId()%10);
    //Attempt to move the piece
    if(gameManager->movePiece(BoardCoordinate(startY,startX),BoardCoordinate(destY,destX))){
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
 * @brief Updates the board based on updated conditions
 */
void ChessboardGUI::update(){
    //Update information/create windows based on updated information
    //Check to see if there are any pawns that need to be promoted
    std::vector<std::vector<ChessPiece*>> boardState = gameManager->getBoardState();
    for(int row : {0,static_cast<int>(gameManager->getBoardHeight()-1)}) {
        for (int col = 0; col < static_cast<int>(gameManager->getBoardWidth()); col++) {
            //Calculate adjusted position, taking board flip into account
            int coordY = static_cast<int>((flip&& gameManager->getPlayerTurn()==Black)?(GameManager::getBoardWidth()+-1-row):row);
            int coordX = static_cast<int>((flip&& gameManager->getPlayerTurn()==Black)?(GameManager::getBoardWidth()-1-col):col);
            if(boardState[coordY][coordX] != nullptr && boardState[coordY][coordX]->getPieceType() == Pawn) {
                //Temporarily promote all pieces to queen for testing
                int promotionType = static_cast<PieceType>(GetPopupMenuSelectionFromUser(*promotionMenu));
                if(promotionType == wxID_NONE){
                    //If user clicks away, abort the move
                    gameManager->undoMove();
                    break;
                }

                //Promote the pawn to the given type
                gameManager->promotePawn(BoardCoordinate(coordY,coordX),static_cast<PieceType>(promotionType));
            }
        }
    }

    //Redraw the board state
    Redraw();

    //Update player's turn
    playerTurn->SetLabelText(wxString(toString(gameManager->getPlayerTurn())));

    //If the king is in check/checkmate, display a pop-up window
    std::set<ChessColor> colors = {White,Black};
    if(gameManager->isKingInCheck()){
        if(gameManager->isKingInCheckmate()){
            wxMessageBox(wxString::Format("%s king is in checkmate\nGame Over",toString(gameManager->getPlayerTurn())), "", wxOK, this);
            gameManager->endGame();
        }
        else{
            wxMessageBox(wxString::Format("%s king is in check",toString(gameManager->getPlayerTurn())), "", wxOK, this);
        }
    }
    else if(gameManager->isStalemate()){
        wxMessageBox(wxString::Format("Stalemate\nGame Over"), "", wxOK, this);
        gameManager->endGame();
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


            int new_width = (currentSquare->m_width > 0)?currentSquare->m_width:1;
            int new_height = (currentSquare->m_height > 0)?currentSquare->m_height:1;

            int coordY = static_cast<int>((flip&& gameManager->getPlayerTurn()==Black)?(GameManager::getBoardHeight()-1-row):row);
            int coordX = static_cast<int>((flip&& gameManager->getPlayerTurn()==Black)?(GameManager::getBoardWidth()-1-col):col);
            if(boardState[coordY][coordX] != nullptr){
                //Add sprites to board where pieces exist
                currentSquare->SetBitmap(wxBitmap(boardState[coordY][coordX]->getSprite().Scale(new_width,new_height)));
                currentSquare->Refresh();
            }
            else{
                //Clear the sprites for squares with no pieces
                currentSquare->SetBitmap(wxBitmap(transparentSquare.Scale(new_width,new_height)));//Attempt to replace with transparent bitmap
                currentSquare->Refresh();
            }
        }
    }

    //Highlight currently selected square (if square is selected)
    if(selectedSquare.y >=0 && selectedSquare.y < static_cast<int>(GameManager::getBoardHeight()) && selectedSquare.x >= 0 && selectedSquare.x < static_cast<int>(GameManager::getBoardWidth())){
        boardSquares[selectedSquare.y][selectedSquare.x]->SetBackgroundColour(wxColor(0x00FF00));
    }
}

/**
 * @brief Sets whether or not the board rotates on Black's turn
 * @param val Whether to rotate the board or not
 */
void ChessboardGUI::setFlip(bool val){
    flip = val;
    Redraw();
}