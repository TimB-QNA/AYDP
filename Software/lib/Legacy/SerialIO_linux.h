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

#ifndef SerialIO_H
  #define SerialIO_H
#include <QtCore>
#include <QtXml>

#include <termios.h>
#include <sys/time.h>
#include <vector>
using namespace std;


class SerialIO : public QObject
{
   Q_OBJECT

public:
  int bufferSizeLimit;
  QByteArray buffer;
  SerialIO(QObject *parent=0);
  void readSettings(QDomNode root);

public slots:
   int open();
  void close();
  void setattr();
  void send(QString string);
  void send(char *string);
  void getData();
  void getData(int);

  void setDevice(QString);
  QString device();
  void setBaud(int);
  int baud();
  void setDataBits(int);
  int dataBits();
  void setParityEn(bool);
  bool parityEn();
  void setParityOdd(bool par);
  bool parityOdd();
  void setStopBits(int);
  int stopBits();
  void setXIN(bool);
  bool XIN();
  void setXOUT(bool);
  bool XOUT();
  void setRTS(bool);
  bool RTS();
  
signals:
  void logData(time_t, int, QString);
  void rawString(QString);
  void newData();

private:
  int fd;
  int baudrate, DParity, DDatabits, DStopbits;
  bool Read, Write, softhandshake;
  QString dev;
  QPointF loc;
  QSocketNotifier *notifier;
  QSettings portSet;
};

#endif

