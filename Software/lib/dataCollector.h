#ifndef DATACOLLECTOR_H
  #define DATACOLLECTOR_H

  #include <QThread>
  #include <QtXml>
  #include "dataStore.h"

class dataCollector : public QThread
{
  public:
    dataCollector(QThread *parent, dataStore *vData);
    virtual void readSettings(QDomNode root);
    
  protected:
    dataStore *vesselData;
};

#endif
