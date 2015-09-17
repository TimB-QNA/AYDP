#include "flightgearWriter.h"
#include <stdio.h>

flightgearWriter::flightgearWriter(QObject *parent) : QObject(parent)
{
  int i;
  fprintf(stderr,"Creating flightgearWriter\n");
  setObjectName("flightgearWriter");
  port=7100;
  
  for (i=0;i<5;i++) channel[i]=0.;
   
  cSkt = new QTcpSocket;
  
  connTimer = new QTimer();
  connTimer->setInterval(1000);
  connect(connTimer, SIGNAL(timeout()), this, SLOT(connToServer()));
  connTimer->start();
  
  outputTimer=new QTimer;
  outputTimer->setInterval(100);
  connect(outputTimer, SIGNAL(timeout()), this, SLOT(writeTCPData()));
}

void flightgearWriter::readSettings(QDomNode root){
  QDomNode node;
  QDomElement element;
  
  if (root.toElement().tagName().toLower()!=objectName().toLower()) return;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="port") port=element.text().toInt();
    node=node.nextSibling();
  }
}

void flightgearWriter::connToServer(){
  int pollRate=100;
  
  if (cSkt->state()!=QAbstractSocket::UnconnectedState){
    printf("Socket not available\n");
    return;
  }
  
  cSkt->connectToHost("127.0.0.1",port);
  if (cSkt->waitForConnected(1000)){
    printf("Output socket connected\n");
    connTimer->stop();
    outputTimer->start();
  }
}

void flightgearWriter::writeTCPData(){
  int i;
  char line[4096];
  
  for (i=0;i<5;i++){
    if (channel[i]>35) channel[i]=35.;
    if (channel[i]<-35) channel[i]=-35.;
  }
  
  if (channel[2]>1) channel[i]=1.;
  if (channel[2]<0) channel[i]=0.;
    
  sprintf(line,"%lf\t%lf\t%lf\t%lf\t%lf\n", -channel[0]/35., channel[1]/35., channel[2], -channel[3]/35., channel[4]/35.);  
  printf("Channels:\t%s",line);

  cSkt->write(line);
}

void flightgearWriter::orderPosition(int ch, float controlValue){
  channel[ch]=controlValue;
}