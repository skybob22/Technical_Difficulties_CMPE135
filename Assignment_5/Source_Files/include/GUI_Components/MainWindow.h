#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wx/wx.h"
#include "ButtonPanel.h"

class MainWindow : public wxFrame{
public:
    explicit MainWindow(wxString title);
    ~MainWindow() override;


    //Event Table
    void OnButtonClicked(wxCommandEvent& evt);
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnSetRounds(wxCommandEvent& evt);
    void OnStartGame(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

private:
    void OnInit();
    void InitMenu();

    wxMenuBar* menuBar;
    ButtonPanel* choicesPanel;
    wxStaticText* choiceLabel;
    wxStaticText* playerChoice;

    enum{
        RPS_EXIT,
        RPS_ABOUT,
        RPS_START_GAME,
        RPS_SET_ROUNDS
    };

};

#endif