#include "ButtonPanel.h"
#include "PlayerChoice.h"
#include "MainWindow.h"

/**
 * @brief Creates a ButtonPanel
 * @param parent The Wx-Widgets parent of the panel
 * @param handler The object in charge of event handling for button clicks
 */
ButtonPanel::ButtonPanel(wxPanel* parent,wxFrame* handler): wxPanel(parent,wxID_ANY),handler(handler){
    OnInit();
}

/**
 * @brief Destroys a ButtonPanel
 */
ButtonPanel::~ButtonPanel() = default;

/**
 * @brief Initializes the layout of a ButtonPanel
 */
void ButtonPanel::OnInit(){
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    choiceLabel = new wxStaticText(this,wxID_ANY,"Choices:");
    sizer->Add(choiceLabel);
    //sizer->AddSpacer(0);

    //Create a sub-panel so that the buttons don't expand to the entire height of the window
    wxPanel* subPanelGrid = new wxPanel(this,wxID_ANY);

    //Create grid of choice buttons (currently only 3, but expandable)
    std::vector<PlayerChoice::Choice> playerChoiceList = PlayerChoice::getEnumList();
    wxGridSizer* grid = new wxGridSizer(1,playerChoiceList.size(),2,2);

    for(PlayerChoice::Choice option : playerChoiceList){
        wxButton* button = new wxButton(subPanelGrid,option,PlayerChoice::toString(option));
        button->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainWindow::OnButtonClicked,dynamic_cast<MainWindow*>(handler));
        grid->Add(button,0,0,0);
        choiceButtons.push_back(button);
    }
    grid->Layout();
    subPanelGrid->SetSizer(grid);
    sizer->Add(subPanelGrid,1,wxALIGN_CENTER_HORIZONTAL);
    //sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}