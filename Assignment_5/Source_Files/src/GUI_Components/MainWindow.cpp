#include "MainWindow.h"
#include "PlayerChoice.h"
#include "ButtonPanel.h"
#include <wx/numdlg.h>

#include "PlayerChoice.h"
#include "Difficulty.h"
#include "Human.h"
#include "HardComputer.h"
#include "GameResult.h"

/**
 * @brief Creates a MainWindow
 * @param title The title of the window
 */
MainWindow::MainWindow(wxString title):wxFrame(nullptr,wxID_ANY,title){
    gameManager = new GameManager;
    gameManager->setNumRounds(20);
    OnInit();
    InitMenu();
}

/**
 * @brief Destroys a MainWindow
 */
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

/**
 * @brief Initializes the layout of the window
 */
void MainWindow::OnInit(){
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //Add current round panel
    wxPanel* roundPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* roundPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* roundLabel = new wxStaticText(roundPanel,wxID_ANY,"Round: ");
    wxFont boldFont = roundLabel->GetFont();
    boldFont.SetPointSize(14);
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);
    //roundLabel->SetFont(boldFont);


    currentRound = new wxStaticText(roundPanel,wxID_ANY,"0 / 20");
    UpdateRound();
    roundPanelSizer->Add(roundLabel,1);
    roundPanelSizer->Add(currentRound,1);
    roundPanel->SetSizer(roundPanelSizer);
    sizer->Add(roundPanel,1,wxALIGN_CENTER_HORIZONTAL);


    //Add human panel
    wxPanel* humanPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* humanSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* humanLabel = new wxStaticText(humanPanel,wxID_ANY,"Human");
    humanLabel->SetFont(boldFont);
    humanSizer->Add(humanLabel,0,wxALIGN_CENTER_HORIZONTAL);

    //Add user choice buttons
    ButtonPanel* choicesPanel = new ButtonPanel(humanPanel,this);
    humanSizer->Add(choicesPanel,1,wxALIGN_CENTER_HORIZONTAL);

    //Add user choice panel
    wxPanel* userChoicePanel = new wxPanel(humanPanel,wxID_ANY);
    wxBoxSizer* choicePanelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* choiceLabel = new wxStaticText(userChoicePanel,wxID_ANY,"Human Choice: ");
    playerChoice = new wxStaticText(userChoicePanel,wxID_ANY,"");
    choicePanelSizer->Add(choiceLabel,1,wxALIGN_LEFT);
    choicePanelSizer->Add(playerChoice,1,wxALIGN_LEFT);
    userChoicePanel->SetSizer(choicePanelSizer);
    humanSizer->Add(userChoicePanel,2,wxALIGN_CENTRE_HORIZONTAL);
    humanPanel->SetSizer(humanSizer);

    sizer->Add(humanPanel,2,wxALIGN_CENTER_HORIZONTAL);



    //Add computer panel
    wxPanel* computerInfoPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* computerInfoSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* computerLabel = new wxStaticText(computerInfoPanel,wxID_ANY,"Computer");
    computerLabel->SetFont(boldFont);
    computerInfoSizer->Add(computerLabel,1,wxALIGN_CENTER_HORIZONTAL);

    //Computer prediction
    wxPanel* computerPredictionPanel = new wxPanel(computerInfoPanel,wxID_ANY);
    wxBoxSizer* computerPredictionSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* predictionLabel = new wxStaticText(computerPredictionPanel,wxID_ANY,"Predicted Human Choice: ");
    computerPrediction = new wxStaticText(computerPredictionPanel,wxID_ANY,"");
    computerPredictionSizer->Add(predictionLabel,1,wxALIGN_LEFT);
    computerPredictionSizer->Add(computerPrediction,1,wxALIGN_LEFT);
    computerPredictionPanel->SetSizer(computerPredictionSizer);
    computerInfoSizer->Add(computerPredictionPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    //Computer Choice
    wxPanel* computerChoicePanel = new wxPanel(computerInfoPanel,wxID_ANY);
    wxBoxSizer* computerChoiceSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* compChoiceLabel = new wxStaticText(computerChoicePanel,wxID_ANY,"Computer Choice: ");
    computerChoice = new wxStaticText(computerChoicePanel,wxID_ANY,"");
    computerChoiceSizer->Add(compChoiceLabel,1,wxALIGN_LEFT);
    computerChoiceSizer->Add(computerChoice,1);
    computerChoicePanel->SetSizer(computerChoiceSizer,wxALIGN_LEFT);
    computerInfoSizer->Add(computerChoicePanel,1,wxALIGN_CENTRE_HORIZONTAL);
    computerInfoPanel->SetSizer(computerInfoSizer);

    sizer->Add(computerInfoPanel,1,wxALIGN_CENTER_HORIZONTAL);
    //Space
    sizer->AddSpacer(50);


    //Add winner panel
    wxPanel* winnerPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* winnerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* winnerLabel = new wxStaticText(winnerPanel,wxID_ANY,"Winner: ");

    winner = new wxStaticText(winnerPanel,wxID_ANY,"");
    winnerSizer->Add(winnerLabel,1,wxALIGN_LEFT);
    winnerSizer->AddSpacer(1);
    winnerSizer->Add(winner,1,wxALIGN_LEFT);
    winnerSizer->AddSpacer(20);

    winnerPanel->SetSizer(winnerSizer);
    sizer->Add(winnerPanel,1,wxALIGN_CENTRE_HORIZONTAL);


    //Add statistics panel
    wxPanel* statisticsPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* statisticsSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* statisticsLabel = new wxStaticText(statisticsPanel,wxID_ANY,"Statistics");
    statisticsLabel->SetFont(boldFont);
    statisticsSizer->Add(statisticsLabel,1,wxALIGN_CENTER_HORIZONTAL);

    //Human wins
    wxPanel* humanWinsPanel = new wxPanel(statisticsPanel,wxID_ANY);
    wxBoxSizer* humanWinsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* humanWinsLabel = new wxStaticText(humanWinsPanel,wxID_ANY,"Human Wins: ");
    humanWins = new wxStaticText(humanWinsPanel,wxID_ANY,"");
    humanWinsSizer->Add(humanWinsLabel,1,wxALIGN_LEFT);
    humanWinsSizer->Add(humanWins,1,wxALIGN_LEFT);
    humanWinsPanel->SetSizer(humanWinsSizer);
    statisticsSizer->Add(humanWinsPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    //Computer wins
    wxPanel* computerWinsPanel = new wxPanel(statisticsPanel,wxID_ANY);
    wxBoxSizer* computerWinsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* computerWinsLabel = new wxStaticText(computerWinsPanel,wxID_ANY,"Computer Wins: ");
    computerWins = new wxStaticText(computerWinsPanel,wxID_ANY,"");
    computerWinsSizer->Add(computerWinsLabel,1,wxALIGN_LEFT);
    computerWinsSizer->Add(computerWins,1,wxALIGN_LEFT);
    computerWinsPanel->SetSizer(computerWinsSizer);
    statisticsSizer->Add(computerWinsPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    //Ties
    wxPanel* tiesPanel = new wxPanel(statisticsPanel,wxID_ANY);
    wxBoxSizer* tiesSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* tiesLabel = new wxStaticText(tiesPanel,wxID_ANY,"Ties: ");
    ties = new wxStaticText(tiesPanel,wxID_ANY,"");
    tiesSizer->Add(tiesLabel,1,wxALIGN_LEFT);
    tiesSizer->Add(ties,1,wxALIGN_LEFT);
    tiesPanel->SetSizer(tiesSizer);
    statisticsSizer->Add(tiesPanel,1,wxALIGN_CENTRE_HORIZONTAL);
    statisticsPanel->SetSizer(statisticsSizer);
    sizer->Add(statisticsPanel,1,wxALIGN_CENTRE_HORIZONTAL);

    sizer->SetSizeHints(this);
    sizer->Layout();
    this->SetSizer(sizer);
}

/**
 * @brief Initializes the layout of the menu bar
 */
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

/**
 * @brief Updates the text for the current round
 */
void MainWindow::UpdateRound(){
    currentRound->SetLabelText(wxString::Format("%u / %u",gameManager->getRound(),gameManager->getNumRounds()));
}

/**
 * @brief Updates the text of the statistics tab
 */
void MainWindow::UpdateStatistics(){
    std::vector<unsigned int> wins = gameManager->getNumWins();
    humanWins->SetLabelText(wxString::Format("%u",wins[1]));
    computerWins->SetLabelText(wxString::Format("%u",wins[2]));
    ties->SetLabelText(wxString::Format("%u",wins[0]));
}

/**
 * @brief Event handler called when "Rock","Paper", or "Scissors" is clicked. Plays a round of Rock-Paper-Scissors
 * @param evt A wxEvent
 */
void MainWindow::OnButtonClicked(wxCommandEvent& evt){
    if (gameManager->isGameInProgress()){
        playerChoice->SetLabelText(PlayerChoice::toString(static_cast<PlayerChoice::Choice>(evt.GetId())));

        //We know player1 is a human
        Human *player1 = dynamic_cast<Human *>(gameManager->game->players[0]);
        player1->setPlayerChoice(static_cast<PlayerChoice::Choice>(evt.GetId()));

        //We know player2 is some type of computer
        Computer *player2 = dynamic_cast<Computer *>(gameManager->game->players[1]);
        if (player2->getDifficulty() == ComputerDifficulty::Difficulty::Hard) {
            //Computer is in hard mode
            HardComputer *computer = dynamic_cast<HardComputer *>(player2);
            computerPrediction->SetLabelText(PlayerChoice::toString(computer->getPrediction()));
        } else {
            //Computer is in easy mode
            computerPrediction->SetLabelText("N/A");
        }

        //Play the next round
        gameManager->playRound();

        //Show results
        GameResult result = gameManager->getMatchHistory().back();
        computerChoice->SetLabelText(PlayerChoice::toString(result.playerChoices[1]));
        winner->SetLabelText((result.winner == 0) ? "Tie" : (result.winner == 1) ? "Human" : "Computer");


        //Update Statistics
        UpdateStatistics();

        //Update which round we are on
        UpdateRound();
    }
    evt.Skip();
}

/**
 * @brief Event handler for when "Exit: is clicked. Causes the app to quit
 * @param evt A wxEvent
 */
void MainWindow::OnExit(wxCommandEvent& evt){
    Close(true);
    evt.Skip();
}

/**
 * @brief Event handler for when "About" is clicked. Displays the info window
 * @param evt A wxEvent
 */
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

/**
 * @brief Event handler for when "Set number of rounds" is clicked. opens pop-up window to get numeric input
 * @param evt A wxEvent
 */
void MainWindow::OnSetRounds(wxCommandEvent& evt){
    unsigned int numRounds  = wxGetNumberFromUser("Enter Number of Rounds","Rounds","Round Selection");
    gameManager->setNumRounds(numRounds);

    UpdateRound();
    evt.Skip();
}

/**
 * @brief Event handler for when difficulty option is selected. Updates the computer's difficulty
 * @param evt A wxEvent
 */
void MainWindow::OnSetDifficulty(wxCommandEvent &evt){
    ComputerDifficulty::Difficulty diff = ((menuBar->FindItem(RPS_HARD)->IsChecked()))?ComputerDifficulty::Difficulty::Hard:ComputerDifficulty::Difficulty::Easy;
    if(gameManager->isGameInProgress()){
        gameManager->game->setPlayerType(2,Player::PlayerType::Computer,diff);
    }
}

/**
 * @brief Event handler for when "Start Game" is clicked. Either starts a new game, or restarts if a game is in progress
 * @param evt A wxEvent
 */
void MainWindow::OnStartGame(wxCommandEvent& evt){
    ComputerDifficulty::Difficulty diff = ((menuBar->FindItem(RPS_HARD)->IsChecked()))?ComputerDifficulty::Difficulty::Hard:ComputerDifficulty::Difficulty::Easy;
    gameManager->startGame(diff);

    UpdateRound();
    UpdateStatistics();
    evt.Skip();
}

/**
 * @brief Event handler for when "End Game" is clicked. Stops the current game
 * @param evt A wxEvent
 */
void MainWindow::OnEndGame(wxCommandEvent& evt){
    gameManager->endGame();
    UpdateRound();
    UpdateStatistics();
    evt.Skip();
}
