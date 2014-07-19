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
#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>

#include <termios.h>
#include <sys/time.h>
#include <vector>
using namespace std;


class QDESIGNER_WIDGET_EXPORT SerialIO : public QWidget
{
   Q_OBJECT
   Q_PROPERTY(QString Device READ device WRITE setDevice)
   Q_PROPERTY(int Baud_Rate READ baud WRITE setBaud)
   Q_PROPERTY(int Data_Bits READ dataBits WRITE setDataBits)
   Q_PROPERTY(bool Parity_En READ parityEn WRITE setParityEn)
   Q_PROPERTY(bool Parity_Odd READ parityOdd WRITE setParityOdd)
   Q_PROPERTY(int Stop_Bits READ stopBits WRITE setStopBits)
   Q_PROPERTY(bool XON_In READ XIN WRITE setXIN)
   Q_PROPERTY(bool XON_Out READ XOUT WRITE setXOUT)
   Q_PROPERTY(bool Use_RTS READ RTS WRITE setRTS)

public:
  int bufferSizeLimit;
  vector<unsigned char> buffer;
  SerialIO(QWidget *parent=0, bool design=false);

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
  bool isDesign;
  QString dev;
  QPointF loc;
  QSocketNotifier *notifier;
  void paintEvent(QPaintEvent *event);
  QSettings portSet;
};

#endif

