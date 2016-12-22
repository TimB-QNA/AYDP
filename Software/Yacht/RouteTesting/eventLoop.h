#ifndef EVENTLOOP_H
  #define EVENTLOOP_H

  #include "../dataStore.h"
  #include "../dataCollector.h"
  #include "../display.h"
  #include "../nmea.h"
  #include "../route.h"

class eventLoop : public QObject
{
  Q_OBJECT
  
  public:
    eventLoop(QObject *parent=0);

  private:
    int gpsCount;
    dataStore vesselData;
    NMEA *nmeaParser;
    route *navRoute;
    QTimer *GPStimer, *routeTimer;
    QStringList nmeaData;
    
    void loadGPSData();
    
  private slots:
    void sendGPSData();
    void processRoute();
};

#endif
