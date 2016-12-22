#ifndef windData_H
  #define windData_H

#include <QtGui>
#include "../Library/gauge.h"
#include "../Library/SerialIO_linux.h"
#include "../Library/aydpCommsProtocol.h"
#include "../Library/qt4gnuplot.h"
/*! Widget to collect wind data and plot a time history on the screen
 *
 */
class windData : public QWidget
{
  Q_OBJECT

  public:
    windData(QWidget *parent=0);
    
  private:
    SerialIO *ioPort;
    aydpCommsProtocol protocol;
    QVector<float> time, windSpeed, windDirection;
    gauge *direction;
    gauge *speed;
    qt4gnuplot *spdGraph;
    qt4gnuplot *dirGraph;
    
  private slots:
    void processData();
};

#endif
