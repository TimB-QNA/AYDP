#ifndef COMMSLINK_H
  #define COMMSLINK_H

  #include <QtCore>
  #include <QtXml>
  #include <QtNetwork>
  #include "dataStore.h"

class commsLink : public QObject
{
  Q_OBJECT
  public:
    commsLink(QObject *parent, dataStore *vData);
    void readSettings(QDomNode root);
    void startServer();
    
  private:
    
    QByteArray checksum(QByteArray msg);
      
    dataStore *vesselData;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> cSkt;
    int port;
    QTimer *dataTimer;
    
  private slots:
    void connection();
    void sendVesselData();
};

#endif
