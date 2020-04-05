#include "MainWindow.h"

MainWindow::MainWindow():wxFrame(nullptr,wxID_ANY,"Roshambo Anytime"){
    choicesPanel = new ButtonPanel(this);
    choicesPanel->Show();
}

MainWindow::~MainWindow() = default;