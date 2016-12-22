#include "logOutput.h"
#include <stdio.h>
#include <QDateTime>
  
logOutput::logOutput(QThread *parent) : QThread(parent)
{
  initialised=false;
  userTimebase=false;
}

void logOutput::setFileName(QString fname){
  logFileName=fname;
}

void logOutput::setUserTimeBase(bool enable){
  userTimebase=enable;
}

void logOutput::setUserTime(float seconds){
  userTime=seconds;
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
  initialised=false;
  logFile=fopen(logFileName.toLatin1().data(),"w");
  if (logFile=='\0'){
    printf("Failed to open log file - %s\n", logFileName.toLatin1().data());
    printf("This log will be disabled\n");
    return;
  }
// Write header line
  fprintf(logFile,"Header Lines\n");
  fprintf(logFile,"Date\tmSecs Since Epoch");
  for (i=0;i<boolHeader.count();i++) fprintf(logFile,"\t%s",boolHeader[i].toLatin1().data());
  for (i=0;i<intHeader.count();i++) fprintf(logFile,"\t%s",intHeader[i].toLatin1().data());
  for (i=0;i<fltHeader.count();i++) fprintf(logFile,"\t%s",fltHeader[i].toLatin1().data());
  for (i=0;i<dblHeader.count();i++) fprintf(logFile,"\t%s",dblHeader[i].toLatin1().data());    
  fprintf(logFile,"\n");
  fflush(logFile);
  initialised=true;
}

void logOutput::writeLogLine(){
  int i;
  if (!initialised) return;
  
  if (!userTimebase){
    QDateTime now=QDateTime::currentDateTimeUtc();
    fprintf(logFile,"%s\t%lli",now.toString("ddMMyy-hhmmss.zzz").toLatin1().data(), now.toMSecsSinceEpoch());
  }else{
    fprintf(logFile,"010170-000000.001\t%i", (int)(userTime*1000.));
  }
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