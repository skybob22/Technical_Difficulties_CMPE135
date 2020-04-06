#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wx/wx.h"
#include "ButtonPanel.h"
#include "GameManager.h"

class GameManager; //Forward declaration

class MainWindow : public wxFrame{
public:
    explicit MainWindow(wxString title);
    ~MainWindow() override;


    //Event Table
    void OnButtonClicked(wxCommandEvent& evt);
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnSetRounds(wxCommandEvent& evt);
    void OnSetDifficulty(wxCommandEvent& evt);
    void OnStartGame(wxCommandEvent& evt);
    void OnEndGame(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

private:
    //Application code
    GameManager* gameManager;

    //Gui code
    void OnInit();
    void InitMenu();
    void UpdateRound();
    void UpdateStatistics();

    wxMenuBar* menuBar;

    //Updated display text
    wxStaticText* currentRound;
    wxStaticText* playerChoice;
    wxStaticText* computerPrediction;
    wxStaticText* computerChoice;
    wxStaticText* winner;
    wxStaticText* humanWins;
    wxStaticText* computerWins;
    wxStaticText* ties;

    enum{
        RPS_EXIT,
        RPS_ABOUT,
        RPS_START_GAME,
        RPS_END_GAME,
        RPS_SET_ROUNDS,
        RPS_EASY,
        RPS_HARD
    };

};

#endif