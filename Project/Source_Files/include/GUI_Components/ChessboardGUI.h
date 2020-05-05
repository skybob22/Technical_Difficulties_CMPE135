#ifndef CHESSBOARD_GUI_H
#define CHESSBOARD_GUI_H

#include "Observer.h"
#include "ChessPiece.h"
#include "ChessTypes.h"
#include "wx/wx.h"
#include <string>

class GameManager; //Forward Declaration
class PromotionWindow; //Forward Declaration

class ChessboardGUI : public wxPanel, public Observer{
public:
    explicit ChessboardGUI(wxFrame* parent,GameManager* gameManager);
    ~ChessboardGUI() override;

    void setColor(ChessColor type,const wxColor& newColor);
    void Redraw();
    void update() override;

private:
    void OnInit();
    void ButtonClicked(wxCommandEvent& evt);
    wxWindow* parent; //TODO: Maybe temporary, remove if not needed

    GameManager* gameManager;
    wxStaticText* playerTurn;

    wxColor whiteColor,blackColor;
    wxImage transparentSquare;
    std::vector<std::vector<wxBitmapButton*>> boardSquares;
    BoardCoordinate selectedSquare;
    wxMenu* promotionMenu;


    const static std::string SPRITE_DIRECTORY;
};

#endif