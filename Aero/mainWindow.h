#ifndef MAINWINDOW_H
  #define MAINWINDOW_H

  #include <QtGui>
  
  #include "../Vessel/src/dataStore.h"
  #include "../Vessel/src/dataCollector.h"
  #include "../Vessel/src/display.h"
  #include "flightgearReader.h"
  #include "flightgearWriter.h"
  #include "../Vessel/src/pidControl.h"
  #include "../Vessel/src/logOutput.h"
  #include "joystick.h"
  #include "joystickStatusDock.h"
  #include "guiPidLoop.h"
  #include "designPanel.h"
  #include "guiDataStore.h"
    
  class mainWindow : public QMainWindow {
  
  Q_OBJECT
  
  public:
    mainWindow(QMainWindow *parent=0);
    void readSettings(QString fileName);

  private:
    dataStore *cds;
    QList<dataCollector*> input;
    flightgearWriter *output;
    guiDataStore *gds;
    
    display *mainScreen;
    logOutput *log;
    
    joystick *tx;
    joystickStatusDock *txDock;
    
    logOutput *rollAPLog;
    pidControl *rollAP;
    
    logOutput *headAPLog;
    pidControl *headAP;

    logOutput *pitchAPLog;
    pidControl *pitchAP;
    
    logOutput *airspeedAPLog;
    pidControl *airspeedAP;
    
    void setupAutopilot();
    
  private slots:
    void joystickControl(int chan, double value);
    void newPlatformData();
//    void enableOutput();
//    void directOutput();
};

#endif
