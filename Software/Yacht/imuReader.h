#ifndef IMUREADER_H
  #define IMUREADER_H
  
  #include "dataCollector.h"
  #include <RTIMULib.h>
  
class imuReader : public dataCollector
{
  Q_OBJECT
  
  public:
    imuReader(QThread *parent, dataStore *vData);   
    void readSettings(QDomNode root);

    void run();
    
  private:
    bool spoof;
    QDateTime sampleTime;
    QTimer *hwPollTimer;
    QString settingsFile;
    RTIMUSettings *settings;
    RTIMU *imu;
    
  private slots:
    void readIMU();
};

#endif
