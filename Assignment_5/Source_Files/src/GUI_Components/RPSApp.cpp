#include "RPSApp.h"

wxIMPLEMENT_APP(RPSApp);

/**
 * @brief Constructs an RPSApp
 */
RPSApp::RPSApp() = default;

/**
 * @brief Destroys an RPSApp
 */
RPSApp::~RPSApp() = default;

/**
 * @brief Wx-Widgets Initializer
 * @return True
 */
bool RPSApp::OnInit(){
    m_frame1 = new MainWindow("Roshambo Anytime");
    m_frame1->Show();

    return true;
}
