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

  private:
    int nChans;
    libusb_context *ctx;
    libusb_device **devList;
    libusb_device  *uAct;
    libusb_device_handle *devHandle;

    void connectDevice();
};

#endif