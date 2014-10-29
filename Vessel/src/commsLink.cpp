#include "commsLink.h"
#include <stdio.h>
#include <sys/time.h>

commsLink::commsLink(QObject *parent, dataStore *vData) : QObject(parent)
{
  vesselData=vData;
  port=6321;
}

void commsLink::readSettings(QDomNode root){
}

void commsLink::startServer(){
  tcpServer = new QTcpServer(this);
  if (!tcpServer->listen(QHostAddress::Any, port)) {
    printf("Unable to start the server: %s.\n", tcpServer->errorString().toAscii().data());
    return;
  }
  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connection()));
  printf("Server is running on port %i.\n", tcpServer->serverPort());
  
  dataTimer = new QTimer();
  dataTimer->setInterval(100);
  connect(dataTimer, SIGNAL(timeout()), this, SLOT(sendData()));
}

void commsLink::connection(){
  cSkt.append( tcpServer->nextPendingConnection() );
  if (!dataTimer->isActive()) dataTimer->start();
}

void commsLink::sendData(){
  int i;
  QByteArray message;
  struct timeval sysTime;
  gettimeofday(&sysTime, NULL);
  
  message.append(0xFF);  
  message.append(17);
  message.append(sizeof(*vesselData));
  message.append((char*)&sysTime,sizeof(sysTime));
  message.append((char*)vesselData,sizeof(*vesselData));
  message.append(checksum(message));
  
  for (i=0;i<message.count();i++){
    printf("0x%02x ",(unsigned char)message.at(i));
  }
  printf("\n");
  
  for (i=0;i<cSkt.count();i++){
    cSkt[i]->write(message);
  }
}

QByteArray commsLink::checksum(QByteArray msg){
  int i;
  char checksum;
  checksum=msg.at(0);
  for (i=1;i<msg.count();i++) checksum^=msg.at(i);
  return QByteArray(&checksum);
}