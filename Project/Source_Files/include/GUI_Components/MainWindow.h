#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ChessboardGUI.h"
#include "wx/wx.h"

class GameManager; //Forward declaration

class MainWindow : public wxFrame{
public:
    explicit MainWindow(wxString title);
    ~MainWindow() override;


    //Event Table
    wxDECLARE_EVENT_TABLE();

private:

    //Gui code
    void OnInit();
    void InitMenu();

    //Callback functions
    void OnResize(wxSizeEvent& event);
    void OnExit(wxCommandEvent& evt);
    void OnStartGame(wxCommandEvent& evt);
    void OnUndoMove(wxCommandEvent& evt);
    void OnSetColor(wxCommandEvent& evt);

    wxMenuBar* menuBar;
    GameManager* gameManager;
    ChessboardGUI* chessboardGUI; //Will eventually need check if pawn is at end and open selector for replacement piece


    //Menu Command Enum
    enum{
        CHESS_EXIT,
        CHESS_START,
        CHESS_UNDO,
        CHESS_BOARD_WHITE,
        CHESS_BOARD_RED
    };
};

#endif
