#ifndef BUTTON_FRAME_H
#define BUTTON_FRAME_H

#include "wx/wx.h"

class ButtonPanel : public wxPanel{
public:
    explicit ButtonPanel(wxFrame* parent);
    ~ButtonPanel() override;

private:
    void OnInit();


    std::vector<wxButton*> choiceButtons;
};

#endif