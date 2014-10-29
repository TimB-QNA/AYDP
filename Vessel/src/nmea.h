/*
    Description: Provide Serial data input for OpenPilot (Class Header)
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 February 2008
        License: GPLv3

Changelog:
    23 February 2008 - v0.1.0 alpha:
        First Release
*/

#ifndef NMEA_H
  #define NMEA_H
#include <QtCore>
#include <QtDesigner/QDesignerExportWidget>
#include "dataCollector.h"
#include "../../Library/SerialIO_linux.h"
#ifdef unix
  #include <sys/time.h>
#endif

/*!
 * All speeds emitted from this class are in m/s.
 */
class NMEA : public dataCollector
{
   Q_OBJECT

  public:
    NMEA(QThread *parent, dataStore *vData);
    void readSettings(QDomNode root);
    void run();
    
  public slots:
    void parseData(QString);

  signals:
    void location(QPointF);
    void fix(int);
    void speed(double);

    void heading(double);
    void altitude(double);
    void track(double);

    void VTGtrack(double);
    void VTGspeed(double);

    void logData(time_t, QString);
    void logData(time_t, int, QString);

    void wind_speed(double);
    void wind_angle(double);
    void wind_speed_relative(double);
    void wind_angle_relative(double);
    void temp_sea_water(double);
    void speed_water(double);
    void dist_total(double);
    void dist_trip(double);
    void depth_offset(double);
    void depth_keel(double);
    void depth_transducer(double);
    void sat_in_view(int, int, int, int);
    void sat_active(int);
    void numActiveSats(int);
    void meanDOP(double);
    void horizontalDOP(double);
    void verticalDOP(double);
    void aisString(QString);

    void openPort();
    void closePort();

  private:
    QByteArray netBuffer;
    QString checksum(QString sentence);
    int invalid;
    SerialIO *dataInterface;
};

#endif

