#include "ButtonPanel.h"
#include "PlayerChoice.h"

ButtonPanel::ButtonPanel(wxWindow* parent): wxPanel(parent,wxID_ANY){
    OnInit();
}

ButtonPanel::~ButtonPanel() = default;

void ButtonPanel::OnInit(){
    //TODO: Resize the buttons and sizer so that they don't take up the entire window

    //Create a sub-panel so that the buttons don't expand to the entire height of the window
    wxPanel* subPanel = new wxPanel(this,wxID_ANY);
    wxSizer* subPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(subPanelSizer);
    subPanelSizer->Add(subPanel,1);

    //Create grid of choice buttons (currently only 3, but expandable)
    std::vector<PlayerChoice::Choice> playerChoiceList = PlayerChoice::getEnumList();
    wxGridSizer* grid = new wxGridSizer(1,playerChoiceList.size(),1,1);
    subPanel->SetSizer(grid);
    for(PlayerChoice::Choice option : playerChoiceList){
        wxButton* button = new wxButton(this,option,PlayerChoice::toString(option));
        button->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&ButtonPanel::OnButtonClicked,this);
        grid->Add(button,1,wxEXPAND);
        choiceButtons.push_back(button);
    }
    grid->Layout();

}

void ButtonPanel::OnButtonClicked(wxCommandEvent &evt){
    //We may need to move this up to the paren in order to handle both "Set Player Choice" and  "Run Game" events
    evt.Skip();
}