#include "ChessApp.h"

wxIMPLEMENT_APP(ChessApp);

/**
 * @brief Constructs an ChessApp
 */
ChessApp::ChessApp() = default;

/**
 * @brief Destroys an ChessApp
 */
ChessApp::~ChessApp() = default;

/**
 * @brief Wx-Widgets Initializer
 * @return True
 */
bool ChessApp::OnInit(){
    m_frame1 = new MainWindow("Chess");
    m_frame1->Show();

    return true;
}
