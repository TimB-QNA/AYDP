#ifndef COMMSLINK_H
  #define COMMSLINK_H

  #include <QtCore>
  #include <QtXml>
  #include <QtNetwork>
  #include "dataStore.h"

typedef struct{
  int datType;
  void *data;
}addrElement;

class commsLink : public QObject
{
  Q_OBJECT
  public:
    enum dataType {uint8=0, uint16, uint32, uint64, int8, int16, int32, int64, float16, float32, float64, boolean};
    commsLink(QObject *parent, dataStore *vData);
    void readSettings(QDomNode root);
    void startServer();
    
    void registerData(unsigned int address, QString label, int type, void *data);
    
  private:
    bool directOutput;
    QByteArray checksum(QByteArray msg);
    dataStore *vesselData;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> cSkt;
    int port;
    QTimer *dataTimer;
    addrElement svuTable[65536];
    
  private slots:
    void connection();
    void sendVesselData();
};

#endif
