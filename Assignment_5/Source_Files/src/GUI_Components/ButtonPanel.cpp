#include "ButtonPanel.h"
#include "PlayerChoice.h"
#include "MainWindow.h"

ButtonPanel::ButtonPanel(wxFrame* parent): wxPanel(parent,wxID_ANY){
    OnInit();
}

ButtonPanel::~ButtonPanel() = default;

void ButtonPanel::OnInit(){
    //TODO: Resize the buttons and sizer so that they don't take up the entire window

    //Create a sub-panel so that the buttons don't expand to the entire height of the window
    wxPanel* subPanel = new wxPanel(this,wxID_ANY);
    wxSizer* subPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(subPanelSizer);
    subPanelSizer->Add(subPanel,1,wxALIGN_CENTER_VERTICAL);

    //Create grid of choice buttons (currently only 3, but expandable)
    std::vector<PlayerChoice::Choice> playerChoiceList = PlayerChoice::getEnumList();
    wxGridSizer* grid = new wxGridSizer(1,playerChoiceList.size(),1,1);
    subPanel->SetSizer(grid);
    for(PlayerChoice::Choice option : playerChoiceList){
        wxButton* button = new wxButton(this,option,PlayerChoice::toString(option));
        button->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainWindow::OnButtonClicked,dynamic_cast<MainWindow*>(m_parent));
        grid->Add(button,1,wxEXPAND);
        choiceButtons.push_back(button);
    }
    grid->Layout();

}