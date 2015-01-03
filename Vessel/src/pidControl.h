#ifndef PIDCONTROL_H
  #define PIDCONTROL_H
  
#include <QThread>
#include <QTimer>
#include <QtXml>
#include "logOutput.h"

class pidControl : public QThread
{
  Q_OBJECT
  
  public:
    pidControl(QThread *parent=0);
    void readSettings(QDomNode root);
    void setupLogOutput(logOutput *logFile);
    void setIterationTime(float it);
    void setCoefficients(float p, float i, float d);
    void setChannel(int c);
    void setSignal(float *v);
    void setDerivative(float *der);
    void setIntegralLimit(float iLim);
    double control();
    
  public slots:
    void setTarget(float t);
    void controlFunction();
  
  private:
    logOutput *log;
    bool calcDerivative;
    int channel;
    float iterTime;
    float intLimit; // Integral term limit. Integral term is ignored for any (absolute) error greater than this value.
    
    float intErrDt; // Integral of error over time
    float error;    // Error between signal and target
    float *dedt;    // Derivative of error with time. This can be passed from an external source, or calculated on the fly.
    
    float *signal, target, controlValue; // signal and target inputs
    float kP, kI, kD; // Coefficients
    QTimer *loopTimer;
    
    void run();
    
  signals:
    void control(int channel, float controlValue);
};

#endif
