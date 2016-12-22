#ifndef NMEA_H
  #define NMEA_H
  
#include <QObject>

class nmea : public QWidget
{
   Q_OBJECT

  public:
    nmea(QWidget *parent=0, bool design=false);

  public slots:
    int  loadFromFile(QString);
    void parseData(QString);
    void logInput(QString input);
    void netInput(QByteArray raw);

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

  private:
    QByteArray netBuffer;
    QString checksum(QString sentence);
};

#endif

