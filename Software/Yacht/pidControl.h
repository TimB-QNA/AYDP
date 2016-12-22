#ifndef PIDCONTROL_H
  #define PIDCONTROL_H

#ifdef GUI
  #include <QWidget>
#else
  #include <QObject>
#endif

#include <QTimer>
#include <QtXml>
#include "logOutput.h"

class pidControl : 
#ifdef GUI
  public QWidget
#else
  public QObject
#endif
{
  Q_OBJECT
  
  public:
        
#ifdef GUI
    pidControl(QWidget *parent=0);
#else
    pidControl(QObject *parent=0);
#endif
        
    void readSettings(QDomNode root);
    void setupLogOutput(logOutput *logFile);
    void setIterationTime(float it);
    void setCoefficients(float p, float i, float d);
    void setChannel(int c);
    void setSignal(float *v);
    void setDerivative(float *der);
    double control();
    float* targetPointer();
    
    void setup();
    
  public slots:
    void setTarget(float t);
    void controlFunction();
    void setPGain(double p);
    void setIGain(double i);
    void setDGain(double d);
    void setIntegralLimit(double iLim);
    void setActive(bool yes);
    bool isActive();
  
  protected:
    logOutput *log;
    bool active;
    bool calcDerivative;
    int channel;
    float iterTime;    
    float intErrDt; // Integral of error over time
    float error;    // Error between signal and target
    float *dedt;    // Derivative of error with time. This can be passed from an external source, or calculated on the fly.
    float *signal, target, controlValue; // signal and target inputs
    float kP, kI, kD; // Coefficients
    float intLimit; // Integral term limit. Integral term is ignored for any (absolute) error greater than this value.

    float oldSignal;
    QTimer *loopTimer;
    
    void initialSetup();
    
  signals:
    void control(int channel, float controlValue);
};

#endif
