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
  dataTimer->setInterval(500);
  connect(dataTimer, SIGNAL(timeout()), this, SLOT(sendData()));
}

void commsLink::connection(){
  cSkt.append( tcpServer->nextPendingConnection() );
  if (!dataTimer->isActive()) dataTimer->start();
  sendData();
}

void commsLink::sendData(){
  int i, nBytes;
  char buff[4096];
  QByteArray message, vData;
  struct timeval sysTime;
  gettimeofday(&sysTime, NULL);
  
  printf("Size of vesselData = %i\n", sizeof(*vesselData));
  
  message.append(0xFF);  
  message.append(17);
  
  vesselData->print();
  vData=vesselData->toByteArray();
  nBytes=vData.count();
  memcpy(buff,&nBytes,sizeof(nBytes)); message.append(buff,sizeof(nBytes));
  memcpy(buff,&sysTime,sizeof(sysTime)); message.append(buff,sizeof(sysTime));
  message.append(vData);
  message.append(checksum(message));
  
  for (i=0;i<message.count();i++){
    printf("0x%02x ",(unsigned char)message.at(i));
  }
  printf("\n");
  
//  FILE *dumpFile;
//  dumpFile=fopen("dumpFile","wb");
//  fwrite(message.data(), message.count(), 1, dumpFile);
//  fclose(dumpFile);
  
  for (i=0;i<cSkt.count();i++){
    cSkt[i]->write(message);
  }
}

QByteArray commsLink::checksum(QByteArray msg){
  int i;
  char checksum;
  checksum=msg.at(0);
  for (i=1;i<msg.count();i++) checksum^=msg.at(i);
  return QByteArray(&checksum,1);
}