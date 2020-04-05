#include "RPSApp.h"

wxIMPLEMENT_APP(RPSApp);

RPSApp::RPSApp() = default;

RPSApp::~RPSApp(){
    delete m_frame1;
}

bool RPSApp::OnInit(){
    m_frame1 = new MainWindow;
    m_frame1->Show();

    return true;
}
