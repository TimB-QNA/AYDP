#include "pidControl.h"
#include <stdio.h>
#include <QDateTime>
#include <math.h>

pidControl::pidControl(QThread *parent) : QThread(parent)
{
  calcDerivative=true; dedt = new float; signal = new float;
  kP=1; kI=0; kD=0; // defaults are a bit arbitrary but acceptable for heading control
  intLimit=0.5;
  channel=0;
  iterTime=50;
  setObjectName("pidControl");
}

void pidControl::readSettings(QDomNode root){
  QDomNode node;
  QDomElement element;
  
  if (root.toElement().tagName().toLower()!=objectName().toLower()) return;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="kp")                  kP=element.text().toFloat();
    if (element.tagName().toLower()=="ki")                  kI=element.text().toFloat();
    if (element.tagName().toLower()=="kd")                  kD=element.text().toFloat();
    if (element.tagName().toLower()=="integrallimit") intLimit=element.text().toFloat();
    if (element.tagName().toLower()=="channel")        channel=element.text().toInt();
    if (element.tagName().toLower()=="iterationtime") iterTime=element.text().toFloat();
    node=node.nextSibling();
  }
}

void pidControl::setupLogOutput(logOutput *logFile){
  log=logFile;
  log->boolean.append(&calcDerivative);  log->boolHeader.append("Calculate Derivative");
  log->integer.append(&channel);         log->intHeader.append("Channel");

  log->flt.append(signal);               log->fltHeader.append("Signal");
  log->flt.append(&target);              log->fltHeader.append("Target");
  log->flt.append(&error);               log->fltHeader.append("Error");
  log->flt.append(&controlValue);        log->fltHeader.append("Control");
  
  log->flt.append(dedt);                 log->fltHeader.append("Derivative");
  log->flt.append(&intErrDt);            log->fltHeader.append("Integral");
  log->flt.append(&intLimit);            log->fltHeader.append("Integral Limit");


  log->flt.append(&kP);             log->fltHeader.append("P coefficient");
  log->flt.append(&kI);             log->fltHeader.append("I coefficient");
  log->flt.append(&kD);             log->fltHeader.append("D coefficient");
}    

void pidControl::setIterationTime(float it){
  iterTime=it;
}

void pidControl::setCoefficients(float p, float i, float d){
  kP=p; kI=i, kD=d;
}

void pidControl::setChannel(int c){
  channel=c;
}

void pidControl::setTarget(float t){
  target=t;  
}

void pidControl::setSignal(float *v){
  delete signal;
  signal=v;
}
    
void pidControl::setDerivative(float *der){
  delete dedt;
  calcDerivative=false;
  dedt=der;
}

void pidControl::setIntegralLimit(float iLim){
  intLimit=iLim;
}
    
void pidControl::run(){
  loopTimer = new QTimer();
  loopTimer->setInterval(iterTime);
  connect(loopTimer, SIGNAL(timeout()), this, SLOT(controlFunction()));
  log->initLogFile();
  loopTimer->start();
  exec();
}

void pidControl::controlFunction(){
  float oldError=error;
  float dt=(float)loopTimer->interval()/1000.;

  error=(*signal)-target;
  intErrDt+=error*dt;
  if (fabs(error)>intLimit) intErrDt=0;
  if (calcDerivative) *dedt=(error-oldError)/dt;
    
  controlValue=error*kP + intErrDt*kI + (*dedt)*kD;
  emit control(channel, controlValue);
  log->writeLogLine();
}

double control(){
  return controlValue;
}