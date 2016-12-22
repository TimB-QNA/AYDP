#ifndef ROUTE_H
  #define ROUTE_H
  
  #include "point.h"
  #include "dataStore.h"
  #include <QObject>
  #include <QtXml>

class route : public QObject
{
  Q_OBJECT
  
  public:
    route(QObject *parent=0);
    void setDataStore(dataStore *ds);
    void loadRouteFromKML(QString filename, QString routeName);
    void calculateDistances(double longitude, double latitude);
    
    double distToNext;
    double headingToNext;
    
  public slots:
    void update();

  private:
    void readPlaceMark(QDomNode root, QString routeName);
    void printWaypoints();
    
    double greatCircleDistance(point p1, point p2);
    double greatCircleHeading(point p1, point p2);
    double pythagoreanDistance(point p1, point p2);
    
    int routeSegment;
    float targetRadius;
    QList<point> routePoint;
    dataStore *cds;
};

#endif
