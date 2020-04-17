#include "MainWindow.h"
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

    chessboardGUI = new ChessboardGUI(this);
    sizer->Add(chessboardGUI,1,wxSHAPED | wxALL | wxALIGN_CENTER);

    sizer->Layout();
    this->SetSizer(sizer);

    //TODO: Adjust these numbers
    this->SetMinSize(wxSize(500,500));

    //For some reason, sizing isn't right during initialization, try redrawing it
    chessboardGUI->Redraw();
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

void MainWindow::OnResize(wxSizeEvent &evt){
    //Bitmaps don't auto-resize, have to redraw board when window resized
    if(chessboardGUI != nullptr){
        chessboardGUI->Redraw();
    }
    evt.Skip();
}

void MainWindow::OnExit(wxCommandEvent& evt){
    Close(true);
    evt.Skip();
}

void MainWindow::OnStartGame(wxCommandEvent& evt){
    if(chessboardGUI != nullptr){
        chessboardGUI->ResetBoard();
    }
    evt.Skip();
}

void MainWindow::OnUndoMove(wxCommandEvent& evt){
    evt.Skip();
}

void MainWindow::OnSetColor(wxCommandEvent& evt){
    //Figure out which color is selected
    wxColor newWhiteColor;
    if(menuBar->FindItem(CHESS_BOARD_WHITE)->IsChecked()){
        newWhiteColor = wxColor(0xFFFFFF);
    }
    else if (menuBar->FindItem(CHESS_BOARD_RED)->IsChecked()){
        newWhiteColor = wxColor(0x0000CC);
    }
    chessboardGUI->setColor(ChessboardGUI::White,newWhiteColor);
    evt.Skip();
}
