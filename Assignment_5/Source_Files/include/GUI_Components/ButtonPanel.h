#ifndef BUTTON_FRAME_H
#define BUTTON_FRAME_H

#include <vector>
#include "wx/wx.h"

class ButtonPanel : public wxPanel{
public:
    explicit ButtonPanel(wxPanel* parent,wxFrame* handler);
    ~ButtonPanel() override;

private:
    void OnInit();

    wxFrame* handler;
    wxStaticText* choiceLabel;
    std::vector<wxButton*> choiceButtons;
};

#endif