#include "MainWindow.h"
#include "PlayerChoice.h"

MainWindow::MainWindow(wxString title):wxFrame(nullptr,wxID_ANY,title){
    OnInit();
    InitMenu();
}

MainWindow::~MainWindow() = default;

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
    EVT_MENU(RPS_EXIT,MainWindow::OnExit)
    EVT_MENU(RPS_ABOUT,MainWindow::OnAbout)
    EVT_MENU(RPS_SET_ROUNDS,MainWindow::OnSetRounds)
    EVT_MENU(RPS_START_GAME,MainWindow::OnStartGame)
wxEND_EVENT_TABLE()

void MainWindow::OnInit(){
    choicesPanel = new ButtonPanel(this);
    choicesPanel->Show();

    //choiceLabel = new wxStaticText(this,wxID_ANY,"Player Choice: ");
    //choiceLabel->Show();

    //playerChoice = new wxStaticText(this,wxID_ANY,"");
    //playerChoice->Show();

}

void MainWindow::InitMenu(){
    menuBar = new wxMenuBar;

    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(RPS_EXIT,"Exit");

    wxMenu* gameMenu = new wxMenu;
    gameMenu->Append(RPS_SET_ROUNDS,"Set Number of Rounds");
    gameMenu->Append(RPS_START_GAME,"Start Game");

    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(RPS_ABOUT,"About");

    menuBar->Append(fileMenu,"File");
    menuBar->Append(gameMenu,"Game");
    menuBar->Append(helpMenu,"Help");
    SetMenuBar(menuBar);
}

void MainWindow::OnButtonClicked(wxCommandEvent &evt){
    //We may need to move this up to the paren in order to handle both "Set Player Choice" and  "Run Game" events
    //playerChoice->SetLabelText(PlayerChoice::toString(static_cast<PlayerChoice::Choice>(evt.GetId())));
    evt.Skip();
}

void MainWindow::OnExit(wxCommandEvent &evt){
    Close(true);
    evt.Skip();
}

void MainWindow::OnAbout(wxCommandEvent &evt){

    evt.Skip();
}

void MainWindow::OnSetRounds(wxCommandEvent &evt){

    evt.Skip();
}

void MainWindow::OnStartGame(wxCommandEvent &evt){

    evt.Skip();
}