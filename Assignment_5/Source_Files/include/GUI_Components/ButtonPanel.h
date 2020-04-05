#ifndef BUTTON_FRAME_H
#define BUTTON_FRAME_H

#include "wx/wx.h"

class ButtonPanel : public wxPanel{
public:
    explicit ButtonPanel(wxWindow* parent);
    ~ButtonPanel() override;

private:
    void OnInit();
    void OnButtonClicked(wxCommandEvent& evt);

    std::vector<wxButton*> choiceButtons;
};

#endif