#include "commsLink.h"
#include <stdio.h>
#include <sys/time.h>

commsLink::commsLink(QObject *parent, dataStore *vData) : QObject(parent)
{
  unsigned int i;
  vesselData=vData;
  port=6321;
  fprintf(stderr,"Integer byte width: %li\n",sizeof(int));
  fprintf(stderr,"  Float byte width: %li\n",sizeof(float));
  fprintf(stderr," Double byte width: %li\n",sizeof(double));
  
  for (i=0;i<65536;i++) svuTable[i].data=NULL;
  directOutput=false;
  registerData(0x0000, "Direct Communications", boolean, &directOutput);
}

void commsLink::readSettings(QDomNode root){
}

void commsLink::startServer(){
  tcpServer = new QTcpServer(this);
  if (!tcpServer->listen(QHostAddress::Any, port)) {
    fprintf(stderr,"Unable to start the server: %s.\n", tcpServer->errorString().toLatin1().data());
    return;
  }
  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connection()));
  fprintf(stderr,"Server is running on port %i.\n", tcpServer->serverPort());
  
  dataTimer = new QTimer();
  dataTimer->setInterval(500);
  connect(dataTimer, SIGNAL(timeout()), this, SLOT(sendVesselData()));
}

void commsLink::connection(){
  cSkt.append( tcpServer->nextPendingConnection() );
  if (!dataTimer->isActive()) dataTimer->start();
  sendVesselData();
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
  fprintf(stderr,"Size of vesselData = %li\n", sizeof(*vesselData));
  
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
  fprintf(stderr,"Size of sysTime = %li\n",sizeof(sysTime));
  message.append(vData);
  message.append(checksum(message));
  
  for (i=0;i<message.count();i++){
    fprintf(stderr,"0x%02x ",(unsigned char)message.at(i));
  }
  fprintf(stderr,"\n");
  
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

void commsLink::registerData(unsigned int address, QString label, int datType, void *data){
  fprintf(stderr,"Registering variable at location 0x%04x as ", address);
  switch(datType){
    case uint8:
      fprintf(stderr,"uint8");
    break;
    case uint16:
      fprintf(stderr,"uint16");
    break;
    case uint32:
      fprintf(stderr,"uint32");
    break;
    case uint64:
      fprintf(stderr,"uint64");
    break;
    case int8:
      fprintf(stderr,"int8");
    break;
    case int16:
      fprintf(stderr,"int16");
    break;
    case int32:
      fprintf(stderr,"int32");
    break;
    case int64:
      fprintf(stderr,"int64");
    break;
    case float16:
      fprintf(stderr,"float16");
    break;
    case float32:
      fprintf(stderr,"float32");
    break;
    case float64:
      fprintf(stderr,"float64");
    break;
    case boolean:
      fprintf(stderr,"boolean");
    break;
    default:
      fprintf(stderr,"unknown");
      break;
  };
  fprintf(stderr," with label \"%s\"\n",label.toLatin1().data());
  svuTable[address].datType=datType;
  svuTable[address].data=data;
}