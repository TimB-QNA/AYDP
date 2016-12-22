#ifndef DATASTORE_H
  #define DATASTORE_H

  #include "logOutput.h"

class dataStore
{
  public:
    dataStore();
    void setupLogOutput(logOutput *log);
    void print(FILE *stream=stderr);
    QByteArray toByteArray();
    dataStore fromByteArray(QByteArray data);
    float roll, pitch, heading;                // Primary IMU outputs
    float rollRate, pitchRate, headingRate;    // Secondary IMU outputs

// GPS-Related values
    double latitude, longitude;                // Position from GPS
    float track, speedOverGround;              // Track over ground, Speed over ground in m/s
    int fixType, actSats;
    float mdop, hdop, vdop;
};

#endif
