#ifndef CALIBRATION_H
  #define CALIDRATION_H

#include <QList>

class calibration
{
  public:
    calibration();
    float calibrated(float in);
    float input;
    bool bounded;
    float lowerBound, upperBound;
    QList<float> coefficient;
};

#endif