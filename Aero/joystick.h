#ifndef joystick_H
  #define joystick_H

#include <QtCore>
#include <time.h>

class joystick : public QThread
{
   Q_OBJECT

  public:
    joystick(QObject *parent=0);
    void setDevice(QString devName);
    unsigned int nAxes;
    unsigned int nButtons;

  private slots:
    bool openDevice();
    bool readData();
    void checkDevice();
    
  private:
    int fd;
    bool cState;
    clock_t lastData;
    QString name;
    QString device;
    QTimer *connTimer;
    QTimer *checkTimer;
    QSocketNotifier *notifier;
    
    void run();
    
  signals:
    void connState(bool);
    void deviceInfo(QString,int,int);
    void axis(int n, double val);
    void button(int n, double val);
};

#endif

