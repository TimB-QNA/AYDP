// Widget to collect wind data and plot historical data on screen

#include "mainWindow.h"

mainWindow::mainWindow(QMainWindow *parent) : QMainWindow(parent){
  QGridLayout *glay = new QGridLayout;
  wind = new windData(); glay->addWidget(wind,0,0);
  setCentralWidget(wind);
  //setLayout(glay);
}
