#ifndef FLIGHTGEARREADER_H
  #define FLIGHTGEARREADER_H
 
  #include <QtNetwork>
  #include "../Vessel/src/dataCollector.h"
  
class flightgearReader : public dataCollector
{
  Q_OBJECT
  
  public:
    flightgearReader(QThread *parent, dataStore *vData);   
    void readSettings(QDomNode root);

    void run();
    
  private:
    int port;
    QDateTime lastMsg;
    QDateTime sampleTime;
    QTcpServer *tcpServer;
    QTcpSocket* cSkt;
    QByteArray buffer;
    
  private slots:
    void connection();
    void readTCPData();
    
  signals:
    void newData();
};

#endif
