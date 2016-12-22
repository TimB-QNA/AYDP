#ifndef EVENTLOOP_H
  #define EVENTLOOP_H

  #include "../dataStore.h"
  #include "../dataCollector.h"

class eventLoop : public QObject
{
  Q_OBJECT
  
  public:
    eventLoop(QObject *parent=0);
    void readSettings(QString fileName);

  private:
    dataStore vesselData;
    QList<dataCollector*> input;
    logOutput *log;
};

#endif
