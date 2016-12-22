#ifndef EVENTLOOP_H
  #define EVENTLOOP_H

  #include "dataStore.h"
#include "dataCollector.h"
#include "display.h"
#include "imuReader.h"
#include "maestro.h"
#include "pidControl.h"
#include "nmea.h"
#include "commsLink.h"
#include "route.h"

class eventLoop : public QObject
{
  Q_OBJECT
  
  public:
    eventLoop(QObject *parent=0);
    void readSettings(QString fileName);

  private:
    dataStore vesselData;
    commsLink *cLink;
    QList<dataCollector*> input;
    display *mainScreen;
    logOutput *log;
    maestro *output;
    logOutput *apLog;
    pidControl *headAP;
    route navRoute;
    
  private slots:
    void enableOutput();
    void directOutput();
};

#endif
