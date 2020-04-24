#ifndef CHESSBOARD_GUI_H
#define CHESSBOARD_GUI_H

#include "Observer.h"
#include "ChessPiece.h"
#include "ChessTypes.h"
#include "wx/wx.h"

class GameManager; //Forward Declaration

class ChessboardGUI : public wxPanel, public Observer{
public:
    explicit ChessboardGUI(wxFrame* parent,GameManager* gameManager);
    ~ChessboardGUI() override;

    void setColor(ChessColor type,const wxColor& newColor);
    void update() override;

private:
    void OnInit();

    GameManager* gameManager;
    wxColor whiteColor,blackColor;

    std::vector<std::vector<wxButton*>> boardSquares;
};

#endif