#ifndef CHESSBOARD_GUI_H
#define CHESSBOARD_GUI_H

#include "ChessPiece.h"
#include "wx/wx.h"

class ChessboardGUI : public wxPanel{
public:
    enum squareType{
        White,
        Black
    };

    explicit ChessboardGUI(wxFrame* parent);
    ~ChessboardGUI();

    void setColor(ChessboardGUI::squareType type,wxColor newColor);
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