#ifndef CHESSAPP_H
#define CHESSAPP_H

#include "wx/wx.h"
#include "MainWindow.h"

class ChessApp : public wxApp{
public:
    ChessApp();
    ~ChessApp() override;

    bool OnInit() override;

private:
    MainWindow* m_frame1;
};

#endif
