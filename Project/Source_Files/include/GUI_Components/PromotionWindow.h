#ifndef PROMOTION_WINDOW_H
#define PROMOTION_WINDOW_H

#include "wx/wx.h"
#include "wx/popupwin.h"

class ChessboardGUI; //Forward declaration

class PromotionWindow : public wxPopupWindow{
public:
    PromotionWindow(wxPanel* parent,ChessboardGUI* GUI);

private:
    void OnInit();

    ChessboardGUI* GUI;
    wxStaticText* testText;
};

#endif
