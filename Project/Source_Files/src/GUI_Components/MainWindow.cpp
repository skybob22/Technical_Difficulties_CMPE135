#include "MainWindow.h"
#include "GameManager.h"
#include <wx/numdlg.h>

/**
 * @brief Creates a MainWindow
 * @param title The title of the window
 */
MainWindow::MainWindow(wxString title):wxFrame(nullptr,wxID_ANY,title),chessboardGUI(nullptr){
    OnInit();
    InitMenu();
}

/**
 * @brief Destroys a MainWindow
 */
MainWindow::~MainWindow(){
}

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
    //Menu Items
    EVT_MENU(CHESS_EXIT,MainWindow::OnExit)
    EVT_MENU(CHESS_START,MainWindow::OnStartGame)
    EVT_MENU(CHESS_UNDO,MainWindow::OnUndoMove)
    //Setting board color
    EVT_MENU(CHESS_BOARD_WHITE,MainWindow::OnSetColor)
    EVT_MENU(CHESS_BOARD_RED,MainWindow::OnSetColor)
    EVT_SIZE(MainWindow::OnResize)
wxEND_EVENT_TABLE()

/**
 * @brief Initializes the layout of the window
 */
void MainWindow::OnInit(){
    wxInitAllImageHandlers();
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    gameManager = new GameManager();

    chessboardGUI = new ChessboardGUI(this,gameManager);
    sizer->Add(chessboardGUI,1,wxSHAPED | wxALL | wxALIGN_CENTER);

    sizer->Layout();
    this->SetSizer(sizer);

    //TODO: Adjust these numbers
    this->SetMinSize(wxSize(500,500));

    //For some reason, sizing isn't right during initialization, try redrawing it
    chessboardGUI->update();
}

/**
 * @brief Initializes the layout of the menu bar
 */
void MainWindow::InitMenu(){
    menuBar = new wxMenuBar;

    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(CHESS_EXIT,"Exit");

    wxMenu* gameMenu = new wxMenu;
    wxMenu* boardMenu = new wxMenu();
    boardMenu->AppendRadioItem(CHESS_BOARD_WHITE,"White");
    boardMenu->AppendRadioItem(CHESS_BOARD_RED,"Red");

    gameMenu->Append(CHESS_START,"Start/Restart Game");
    gameMenu->Append(CHESS_UNDO,"Undo");
    gameMenu->AppendSubMenu(boardMenu,"Board Color");

    menuBar->Append(fileMenu,"File");
    menuBar->Append(gameMenu,"Game");
    SetMenuBar(menuBar);
}

/**
 * @brief Called when the window is resized
 * @param evt An event
 */
void MainWindow::OnResize(wxSizeEvent &evt){
    //Bitmaps don't auto-resize, have to redraw board when window resized
    if(chessboardGUI != nullptr){
        chessboardGUI->update();
    }
    evt.Skip();
}

/**
 * @brief Called when the user clicks on exit, quits the program
 * @param evt An event
 */
void MainWindow::OnExit(wxCommandEvent& evt){
    Close(true);
    evt.Skip();
}

/**
 * @brief Called when the user clicks new game, starts a new game
 * @param evt An event
 */
void MainWindow::OnStartGame(wxCommandEvent& evt){
    if(gameManager != nullptr){
        gameManager->newGame();
    }
    evt.Skip();
}

/**
 * @brief Called when the user clicks undo, undoes the last move
 * @param evt An event
 */
void MainWindow::OnUndoMove(wxCommandEvent& evt){
    gameManager->undoMove();
    evt.Skip();
}

/**
 * @brief Called when the user selects a color for the board, changes the current color
 * @param evt An event
 */
void MainWindow::OnSetColor(wxCommandEvent& evt){
    //Figure out which color is selected
    wxColor newWhiteColor;
    if(menuBar->FindItem(CHESS_BOARD_WHITE)->IsChecked()){
        newWhiteColor = wxColor(0xFFFFFF);
    }
    else if (menuBar->FindItem(CHESS_BOARD_RED)->IsChecked()){
        newWhiteColor = wxColor(0x0000CC);
    }
    chessboardGUI->setColor(ChessColor::White,newWhiteColor);
    evt.Skip();
}
