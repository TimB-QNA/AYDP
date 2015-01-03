#include "logOutput.h"
#include <stdio.h>
#include <QDateTime>
  
logOutput::logOutput(QThread *parent) : QThread(parent)
{
  initialised=false;
}

void logOutput::setFileName(QString fname){
  logFileName=fname;
}

void logOutput::readSettings(QDomNode root){
  
}

void logOutput::run(){
  initLogFile();

  logTimer = new QTimer();
  logTimer->setInterval(20);
  connect(logTimer, SIGNAL(timeout()), this, SLOT(writeLogLine()));
  logTimer->start();
  exec();
}

void logOutput::initLogFile(){
  int i;
// Open log file
  logFile=fopen(logFileName.toAscii().data(),"w");
// Write header line
  fprintf(logFile,"Header Lines\n");
  fprintf(logFile,"Date\tmSecs Since Epoch");
  for (i=0;i<boolHeader.count();i++) fprintf(logFile,"\t%s",boolHeader[i].toAscii().data());
  for (i=0;i<intHeader.count();i++) fprintf(logFile,"\t%s",intHeader[i].toAscii().data());
  for (i=0;i<fltHeader.count();i++) fprintf(logFile,"\t%s",fltHeader[i].toAscii().data());
  for (i=0;i<dblHeader.count();i++) fprintf(logFile,"\t%s",dblHeader[i].toAscii().data());    
  fprintf(logFile,"\n");
  initialised=true;
}

void logOutput::writeLogLine(){
  int i;
  if (!initialised) return;
  
  QDateTime now=QDateTime::currentDateTimeUtc();
  fprintf(logFile,"%s\t%lli",now.toString("ddMMyy-hhmmss.zzz").toAscii().data(), now.toMSecsSinceEpoch());
  for (i=0;i<boolean.count();i++){
    if (*boolean[i]==true){
      fprintf(logFile,"\t1");
    }else{
      fprintf(logFile,"\t0");
    }
  }
  for (i=0;i<integer.count();i++) fprintf(logFile,"\t%i",*integer[i]);
  for (i=0;i<flt.count();i++)     fprintf(logFile,"\t%f",*flt[i]);
  for (i=0;i<dbl.count();i++)     fprintf(logFile,"\t%lf",*dbl[i]);
  fprintf(logFile,"\n");
}