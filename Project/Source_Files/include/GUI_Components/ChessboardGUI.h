#ifndef CHESSBOARD_GUI_H
#define CHESSBOARD_GUI_H

#include "ChessPiece.h"
#include "ChessTypes.h"
#include "wx/wx.h"

class ChessboardGUI : public wxPanel{
public:
    explicit ChessboardGUI(wxFrame* parent);
    ~ChessboardGUI() override;

    void setColor(ChessColor type,const wxColor& newColor);
    void ResetBoard();
    void Redraw();

private:
    void OnInit();

    wxColor whiteColor,blackColor;

    std::vector<std::vector<wxButton*>> boardSquares;
    std::vector<std::vector<ChessPiece*>> chessPieces;

    const static unsigned int BOARD_WIDTH,BOARD_HEIGHT;
};

#endif