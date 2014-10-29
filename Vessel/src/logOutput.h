#ifndef LOGOUTPUT_H
  #define LOGOUTPUT_H
  
#include <stdio.h>
#include <stdlib.h>
#include <QtXml>
#include <QList>
#include <QStringList>
#include <QThread>
#include <QTimer>

class logOutput : public QThread
{
  Q_OBJECT
  
  public:
    logOutput(QThread *parent=0);
    void readSettings(QDomNode root);
    void setFileName(QString fname);
    void initLogFile();
    QStringList boolHeader;
    QList<bool*> boolean;
    QStringList intHeader;
    QList<int*> integer;
    QStringList fltHeader;
    QList<float*> flt;
    QStringList dblHeader;
    QList<double*> dbl;
    
  public slots:
    void writeLogLine();
    
  private:
    FILE *logFile;
    QTimer *logTimer;
    QString logFileName;
    void run();
};

#endif
