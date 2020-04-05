#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wx/wx.h"
#include "ButtonPanel.h"

class MainWindow : public wxFrame{
public:
    MainWindow();
    ~MainWindow() override;

private:
    ButtonPanel* choicesPanel;

};

#endif