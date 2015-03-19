#include "commsLink.h"
#include <stdio.h>
#include <sys/time.h>

commsLink::commsLink(QObject *parent, dataStore *vData) : QObject(parent)
{
  vesselData=vData;
  port=6321;
  printf("Integer byte width: %li\n",sizeof(int));
  printf("  Float byte width: %li\n",sizeof(float));
  printf(" Double byte width: %li\n",sizeof(double));
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
  connect(dataTimer, SIGNAL(timeout()), this, SLOT(sendVesselData()));
}

void commsLink::connection(){
  cSkt.append( tcpServer->nextPendingConnection() );
  if (!dataTimer->isActive()) dataTimer->start();
  sendData();
}
/*!
 * Raspberry PI is supported in this function by use of the __arm__ pre-processor definition. This
 * could cause issues with other arm processors.
 */
void commsLink::sendVesselData(){
  int i, nBytes;
  char buff[4096];
  QByteArray message, vData;
  struct timeval sysTime;
// Raspberry PI support
#ifdef __arm__
  long long int sysSeconds;
  long long int sysMicros;
#endif
  
  gettimeofday(&sysTime, NULL);
#ifdef __arm__
  sysSeconds=sysTime.tv_sec;
  sysMicros=sysTime.tv_usec;
#endif
  system("clear");
  printf("Size of vesselData = %li\n", sizeof(*vesselData));
  
  message.append(0xFF);  
  message.append(17);
  
  vesselData->print();
  vData=vesselData->toByteArray();
  nBytes=vData.count();

  memcpy(buff,&nBytes,sizeof(nBytes)); message.append(buff,sizeof(nBytes));
#ifdef __arm__
  memcpy(buff,&sysSeconds,sizeof(sysSeconds)); message.append(buff,sizeof(sysSeconds));
  memcpy(buff,&sysMicros, sizeof(sysMicros));  message.append(buff,sizeof(sysMicros));
#else
  memcpy(buff,&sysTime,sizeof(sysTime)); message.append(buff,sizeof(sysTime));
#endif  
  printf("Size of sysTime = %li\n",sizeof(sysTime));
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