#ifndef MAESTRO_H
  #define MAESTRO_H
  
#include <QtCore>
#include <QString>
#include <libusb-1.0/libusb.h>
#include "calibration.h"

class maestro : public QObject
{
   Q_OBJECT

  public:
    maestro(QObject *parent=0);
    QVector<calibration> channel;
    
  public slots:
    void orderPosition(int servo, float position);
    void listDevices();
    void grabDevice(QString serialNo="00009132");
    int channels();
    void setSpeed(int srv, double value);
    void setAcceleration(int srv, unsigned char value);

  private:
    int REQUEST_SET_SERVO_VARIABLE;
    int REQUEST_SET_TARGET;
    
    int nChans;
    libusb_context *ctx;
    libusb_device **devList;
    libusb_device  *uAct;
    libusb_device_handle *devHandle;

    void connectDevice();
};

#endif