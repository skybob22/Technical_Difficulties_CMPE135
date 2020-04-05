#ifndef RPSAPP_H
#define RPSAPP_H

#include "wx/wx.h"
#include "MainWindow.h"

class RPSApp : public wxApp{
public:
    RPSApp();
    ~RPSApp() override;

    bool OnInit() override;

private:
    MainWindow* m_frame1;
};

#endif
