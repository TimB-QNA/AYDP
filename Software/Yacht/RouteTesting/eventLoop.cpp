#include "eventLoop.h"
#include <stdio.h>

eventLoop::eventLoop(QObject *parent) : QObject(parent)
{
  int i;
  
  navRoute = new route;
  navRoute->setDataStore(&vesselData);
  navRoute->loadRouteFromKML("ComparisonRoute.kml", QString());
  loadGPSData();

  nmeaParser = new NMEA(0, &vesselData);

  GPStimer = new QTimer;
  GPStimer->setInterval(50);
  GPStimer->start();
  connect(GPStimer, SIGNAL(timeout()), this, SLOT(sendGPSData()));
  connect(nmeaParser, SIGNAL(location(QPointF)), navRoute, SLOT(update()));
//  routeTimer = new QTimer;
//  routeTimer->setInterval(1000);
//  routeTimer->start();
//  connect(routeTimer, SIGNAL(timeout()), this, SLOT(processRoute()));
}

void eventLoop::loadGPSData(){
  QFile inFile;
  inFile.setFileName("gps-sample-1Hz-2.txt");
  
  if (inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
    nmeaData.clear();
    while (!inFile.atEnd()) {
      nmeaData.append(inFile.readLine());
    }
    inFile.close();
  }
}

void eventLoop::sendGPSData(){
  if (gpsCount==nmeaData.count()) GPStimer->stop();
  nmeaParser->parseData(nmeaData[gpsCount]);
  gpsCount++;
}

void eventLoop::processRoute(){
  printf("Processing Route\n");
  navRoute->calculateDistances(vesselData.longitude, vesselData.latitude);
}