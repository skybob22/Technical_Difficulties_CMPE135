#include "MainWindow.h"
#include "PlayerChoice.h"
#include "ButtonPanel.h"
#include <wx/numdlg.h>

MainWindow::MainWindow(wxString title):wxFrame(nullptr,wxID_ANY,title){
    OnInit();
    InitMenu();

    gameManager = new GameManager;
}

MainWindow::~MainWindow(){
    delete gameManager;
}

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
    //Menu Items
    EVT_MENU(RPS_EXIT,MainWindow::OnExit)
    EVT_MENU(RPS_ABOUT,MainWindow::OnAbout)
    EVT_MENU(RPS_SET_ROUNDS,MainWindow::OnSetRounds)
    EVT_MENU(RPS_START_GAME,MainWindow::OnStartGame)
    EVT_MENU(RPS_END_GAME,MainWindow::OnEndGame)

    //Difficulty Selection
    EVT_MENU(RPS_EASY,MainWindow::OnSetDifficulty)
    EVT_MENU(RPS_HARD,MainWindow::OnSetDifficulty)
wxEND_EVENT_TABLE()

void MainWindow::OnInit(){
    //TODO: All labels start with default value N/A, maybe adjust later?
    //TODO: Positioning is all wonky, will want to adjust
    //TODO: Text sometimes doesn't show/resize properly. Try to find out why
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //Add current round panel
    wxPanel* roundPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* roundPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* roundLabel = new wxStaticText(roundPanel,wxID_ANY,"Round: ");
    currentRound = new wxStaticText(roundPanel,wxID_ANY,"0 / 0");
    roundPanelSizer->Add(roundLabel,1);
    roundPanelSizer->Add(currentRound,1);
    roundPanel->SetSizer(roundPanelSizer);
    sizer->Add(roundPanel,1,wxALIGN_CENTER_HORIZONTAL);
    //Space
    sizer->AddSpacer(10);


    //Add human panel
    wxPanel* humanPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* humanSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* humanLabel = new wxStaticText(humanPanel,wxID_ANY,"Human");
    humanSizer->Add(humanLabel,1,wxALIGN_CENTER_HORIZONTAL);

    //Add user choice buttons
    ButtonPanel* choicesPanel = new ButtonPanel(humanPanel,this);
    humanSizer->Add(choicesPanel,1,wxALIGN_CENTER_HORIZONTAL);

    //Add user choice panel
    wxPanel* userChoicePanel = new wxPanel(humanPanel,wxID_ANY);
    wxBoxSizer* choicePanelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* choiceLabel = new wxStaticText(userChoicePanel,wxID_ANY,"Human Choice: ");
    playerChoice = new wxStaticText(userChoicePanel,wxID_ANY,"N/A");
    choicePanelSizer->Add(choiceLabel,1);
    choicePanelSizer->Add(playerChoice,1);
    humanSizer->Add(userChoicePanel,1,wxALIGN_CENTRE_HORIZONTAL);

    humanPanel->SetSizer(humanSizer);
    sizer->Add(humanPanel,1,wxALIGN_CENTER_HORIZONTAL);



    //Add computer panel
    wxPanel* computerInfoPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* computerInfoSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* computerLabel = new wxStaticText(computerInfoPanel,wxID_ANY,"Computer");
    computerInfoSizer->Add(computerLabel,1,wxALIGN_CENTER_HORIZONTAL);

    //Computer prediction
    wxPanel* computerPredictionPanel = new wxPanel(computerInfoPanel,wxID_ANY);
    wxBoxSizer* computerPredictionSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* predictionLabel = new wxStaticText(computerPredictionPanel,wxID_ANY,"Predicted Human Choice: ");
    computerPrediction = new wxStaticText(computerPredictionPanel,wxID_ANY,"N/A");
    computerPredictionSizer->Add(predictionLabel,1);
    computerPredictionSizer->Add(computerPrediction,1);
    computerPredictionPanel->SetSizer(computerPredictionSizer);
    computerInfoSizer->Add(computerPredictionPanel,1,wxALIGN_CENTRE_HORIZONTAL);
    computerInfoSizer->AddSpacer(5);

    //Computer Choice
    wxPanel* computerChoicePanel = new wxPanel(computerInfoPanel,wxID_ANY);
    wxBoxSizer* computerChoiceSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* compChoiceLabel = new wxStaticText(computerChoicePanel,wxID_ANY,"Computer Choice: ");
    computerChoice = new wxStaticText(computerChoicePanel,wxID_ANY,"N/A");
    computerChoiceSizer->Add(compChoiceLabel,1);
    computerChoiceSizer->Add(computerChoice,1);
    computerChoicePanel->SetSizer(computerChoiceSizer);
    computerInfoSizer->Add(computerChoicePanel,1,wxALIGN_CENTRE_HORIZONTAL);
    computerInfoPanel->SetSizer(computerInfoSizer);

    sizer->Add(computerInfoPanel,1,wxALIGN_CENTER_HORIZONTAL);
    //Space
    sizer->AddSpacer(10);


    //Add winner panel
    wxPanel* winnerPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* winnerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* winnerLabel = new wxStaticText(winnerPanel,wxID_ANY,"Winner: ");
    winner = new wxStaticText(winnerPanel,wxID_ANY,"N/A");
    winnerSizer->Add(winnerLabel,1);
    winnerSizer->Add(winner,1);
    winnerPanel->SetSizer(winnerSizer);
    sizer->Add(winnerPanel,1,wxALIGN_CENTRE_HORIZONTAL);
    //Space
    sizer->AddSpacer(10);




    //Add statistics panel
    wxPanel* statisticsPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* statisticsSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* statisticsLabel = new wxStaticText(statisticsPanel,wxID_ANY,"Statistics");
    statisticsSizer->Add(statisticsLabel,1,wxALIGN_CENTER_HORIZONTAL);

    //Human wins
    wxPanel* humanWinsPanel = new wxPanel(statisticsPanel,wxID_ANY);
    wxBoxSizer* humanWinsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* humanWinsLabel = new wxStaticText(humanWinsPanel,wxID_ANY,"Human Wins: ");
    humanWins = new wxStaticText(humanWinsPanel,wxID_ANY,"N/A");
    humanWinsSizer->Add(humanWinsLabel,1);
    humanWinsSizer->Add(humanWins,1);
    humanWinsPanel->SetSizer(humanWinsSizer);
    statisticsSizer->Add(humanWinsPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    //Computer wins
    wxPanel* computerWinsPanel = new wxPanel(statisticsPanel,wxID_ANY);
    wxBoxSizer* computerWinsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* computerWinsLabel = new wxStaticText(computerWinsPanel,wxID_ANY,"Computer Wins: ");
    computerWins = new wxStaticText(computerWinsPanel,wxID_ANY,"N/A");
    computerWinsSizer->Add(computerWinsLabel,1);
    computerWinsSizer->Add(computerWins,1);
    computerWinsPanel->SetSizer(computerWinsSizer);
    statisticsSizer->Add(computerWinsPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    //Ties
    wxPanel* tiesPanel = new wxPanel(statisticsPanel,wxID_ANY);
    wxBoxSizer* tiesSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* tiesLabel = new wxStaticText(tiesPanel,wxID_ANY,"Ties: ");
    ties = new wxStaticText(tiesPanel,wxID_ANY,"N/A");
    tiesSizer->Add(tiesLabel,1);
    tiesSizer->Add(ties,1);
    tiesPanel->SetSizer(tiesSizer);
    statisticsSizer->Add(tiesPanel,1,wxALIGN_CENTRE_HORIZONTAL);
    statisticsPanel->SetSizer(statisticsSizer);
    sizer->Add(statisticsPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    this->SetSizer(sizer);
}

void MainWindow::InitMenu(){
    menuBar = new wxMenuBar;

    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(RPS_EXIT,"Exit");

    wxMenu* gameMenu = new wxMenu;
    wxMenu* difficultyMenu = new wxMenu();
    difficultyMenu->AppendRadioItem(RPS_HARD,"Hard");
    difficultyMenu->AppendRadioItem(RPS_EASY,"Easy");

    gameMenu->Append(RPS_SET_ROUNDS,"Set Number of Rounds");
    gameMenu->AppendSubMenu(difficultyMenu,"Difficulty");
    gameMenu->AppendSeparator();
    gameMenu->Append(RPS_START_GAME,"Start/Restart Game");
    gameMenu->Append(RPS_END_GAME,"End Game");

    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(RPS_ABOUT,"About");

    menuBar->Append(fileMenu,"File");
    menuBar->Append(gameMenu,"Game");
    menuBar->Append(helpMenu,"Help");
    SetMenuBar(menuBar);
}

void MainWindow::OnButtonClicked(wxCommandEvent& evt){
    playerChoice->SetLabelText(wxString::Format("Human Choice: %s",PlayerChoice::toString(static_cast<PlayerChoice::Choice>(evt.GetId()))));
    evt.Skip();
}

void MainWindow::OnExit(wxCommandEvent& evt){
    Close(true);
    evt.Skip();
}

void MainWindow::OnAbout(wxCommandEvent& evt){
    wxMessageBox(wxString::Format(
            "This is a Gui-Based Rock-Paper-Scissors game\n"
            "Built by: Jonathan Beard, Cameron Lofy, George Makhoul & Steven West\n\n"
            "Framework: %s\n"
            "Platform: %s.",
            wxVERSION_STRING,
            wxGetOsDescription()
            ),"About the program",
                    wxOK | wxICON_INFORMATION,
                    this);
    evt.Skip();
}

void MainWindow::OnSetRounds(wxCommandEvent& evt){
    unsigned int numRounds  = wxGetNumberFromUser("Enter Number of Rounds","Rounds","Round Selection");
    gameManager->setNumRounds(numRounds);

    currentRound->SetLabelText(wxString::Format("%u / %u",gameManager->getRound(),gameManager->getNumRounds()));
    evt.Skip();
}

void MainWindow::OnSetDifficulty(wxCommandEvent &evt){
    //TODO:Currently restarts game with new difficulty, maybe allow changing halfway through?
    OnStartGame(evt);
}

void MainWindow::OnStartGame(wxCommandEvent& evt){
    std::string diff = ((menuBar->FindItem(RPS_HARD)->IsChecked()))?"Hard":"Easy";
    wxMessageBox(wxString::Format("Temp: Starting game with difficulty %s",diff));
    evt.Skip();
}

void MainWindow::OnEndGame(wxCommandEvent& evt){

    evt.Skip();
}