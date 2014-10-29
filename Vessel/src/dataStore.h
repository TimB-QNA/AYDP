#ifndef DATASTORE_H
  #define DATASTORE_H

  #include "logOutput.h"

class dataStore
{
  public:
    dataStore();
    void setupLogOutput(logOutput *log);
    float roll, pitch, heading;                // Primary IMU outputs
    float rollRate, pitchRate, headingRate;    // Secondary IMU outputs

// GPS-Related values
    double latitude, longitude;                // Position from GPS
    float track, speedOverGround;              // Track over ground, Speed over ground in m/s
    int fixType, actSats;
    double mdop, hdop, vdop;
    
  private:
    QString logFile;
    QString name;
    void run();
};

#endif
