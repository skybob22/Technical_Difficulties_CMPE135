#include "RPSApp.h"

wxIMPLEMENT_APP(RPSApp);

RPSApp::RPSApp() = default;

RPSApp::~RPSApp() = default;

bool RPSApp::OnInit(){
    m_frame1 = new MainWindow("Roshambo Anytime");
    m_frame1->Show();

    return true;
}
