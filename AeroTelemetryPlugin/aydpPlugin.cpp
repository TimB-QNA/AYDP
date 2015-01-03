#include "aydpPlugin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "../Vessel/src/dataStore.h"

aydpPlugin::aydpPlugin(QObject *parent) : QObject(parent){
  statText="AYDP";
  statIndicator = new QLabel(QString("<html><font color='red'>")+statText+QString("</font></html>"));
  
  connTimer = new QTimer();
  connTimer->setInterval(5000);
  connTimer->setSingleShot(true);
  connect(connTimer, SIGNAL(timeout()), this, SLOT(checkForConnection()));
  
  m_dockWidget = new aydpDockWidget(0, &vData);
}

QObject* aydpPlugin::asQObject(){
  return this;  
}

QString aydpPlugin::pluginName(){
  return QString("aydpNetwork");
}

QString aydpPlugin::pluginDescription(){
  return QString("Allows communication with all AYDP systems.");
}

QString aydpPlugin::xmlRootTag(){
  return QString("aydpNet");
}

void aydpPlugin::readXML(QDomNode root){
  printf("Reading AYDP Plugin XML\n");
  settings.readXML(root);
  emit pluginRunning();
}

QStringList aydpPlugin::writeXML(){
  printf("Writing AYDP Plugin XML\n");
  return settings.writeXML();
}
QWidget* aydpPlugin::dockWidget(){
  return m_dockWidget;
}

QWidget* aydpPlugin::statusIndicator(){
  return statIndicator; 
}

void aydpPlugin::connectToPeer(){
  bool connOK=false;
  if (settings.deviceType==aydpSettings::tcpip)   statText=QString("AYDP-TCP");
  if (settings.deviceType==aydpSettings::serial)    statText=QString("AYDP-Ser");
  if (settings.deviceType==aydpSettings::bluetooth) statText=QString("AYDP-BT");
  statIndicator->setText(QString("<html><font color='yellow'>")+statText+QString("</font></html>"));
  
  connTimer->setInterval(settings.reconnectRate);
    
  if (settings.deviceType==aydpSettings::tcpip){
    connOK=connectTCPIP();
  }
  
  if (settings.deviceType==aydpSettings::bluetooth){
    connOK=connectBluetooth();
  }
  
  if (connOK) statIndicator->setText(QString("<html><font color='green'>")+statText+QString("</font></html>"));
  if (!connOK) statIndicator->setText(QString("<html><font color='red'>")+statText+QString("</font></html>"));
}

bool aydpPlugin::connectBluetooth(){
  struct sockaddr_rc addr;
  int status;

  printf("AYDP Plugin -- Connecting to Bluetooth device... Please wait.\n");
    
  // allocate a socket
  bt_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // set the connection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( settings.host.toAscii().data(), &addr.rc_bdaddr );

  // connect to server
  status = ::connect(bt_socket, (struct sockaddr *)&addr, sizeof(addr));
      
  if( status < 0 ){
    printf("AYDP Network -- Failed to connect. Retrying in %.1lf seconds.\n", settings.reconnectRate/1000.);
    connTimer->start();
  }else{
    printf("AYDP Network -- Connection established.\n");
    socketNotify = new QSocketNotifier(bt_socket, QSocketNotifier::Read, this);
    connect(socketNotify, SIGNAL(activated(int)), this, SLOT(readData(int)));
    return true;
  }
  return false;
}

void aydpPlugin::disconnectFromPeer(){
  disconnected();
}

void aydpPlugin::disconnected(){
  statIndicator->setText(QString("<html><font color='red'>")+statText+QString("</font></html>"));
}

bool aydpPlugin::connectTCPIP(){
  TCPClient=new QTcpSocket();
  TCPClient->connectToHost(settings.host, settings.port);
  if (!TCPClient->waitForConnected(settings.connectTimeout)){
    printf("AYDP Plugin -- Failed to connect %s:%i\n",settings.host.toAscii().data(), settings.port); // - Retrying in %1 milliseconds").arg(settings.reconnectRate));
    delete TCPClient;
    return false;
//    connTimer->start();
  }
  
  connect(TCPClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(TCPClient, SIGNAL(readyRead()), this, SLOT(readTCPData()));
//  idleConnTimer->start();
//  onConnection();
//  emit connected(true);
//  debug.output(1,QString("Client %1 connected, using "+protocol+protocolMode).arg(tcpSocket.size()-1));
  return true;
}

void aydpPlugin::readTCPData(){
  int i, j;
  unsigned char opCode;
  unsigned int nBytes;
  struct timeval msgTime;
  QDateTime msgDateTime;
  unsigned char checksum;
  unsigned char data[4096];
  telemetryDataPoint tmpData;
  
  buffer+=TCPClient->readAll();
  
//  printf("Integer byte width: %i\n",sizeof(int));
//  printf("  Float byte width: %i\n",sizeof(float));
//  printf(" Double byte width: %i\n",sizeof(double));
  
//  printf("        Byte No: ");
//  for (j=0;j<buffer.size();j++) printf("%04i ", j);
//  printf("\n");
//  printf("Buffer Contents: ");
//  for (i=0;i<buffer.size();i++){
//    printf("0x%02x ",(unsigned char)buffer[i]);
//  }
//  printf("\nParsing:\n");
  // Now parse data in the buffer...
  for (i=0;i<buffer.size();i++){
    if (buffer[i]!=(char)0xff) continue;
    if (i>(buffer.size()-22)) return; // Insufficient data, wait for more

//    printf("Start bit found at byte %i\n",i);
    memcpy(&opCode,buffer.data()+(i+1),sizeof(opCode));
//    printf("OpCode = %i\n",opCode);
    memcpy(&nBytes,buffer.data()+(i+2),sizeof(nBytes));
//    printf("nBytes = %i\n",nBytes);
    memcpy(&msgTime,buffer.data()+(i+6),sizeof(msgTime));
    msgDateTime=QDateTime::fromTime_t(msgTime.tv_sec);
    msgDateTime.addMSecs((int)((float)msgTime.tv_usec/1000.+0.5));
//    printf("Message sent at %s\n",msgDateTime.toString("dd/MM/yyyy hh:mm:ss.zzz").toAscii().data());
    
    if (i>buffer.size()-22-nBytes){
      // Then we don't have enough data, so we'll wait for more...
      return;
    }
        
    checksum=createChecksum((unsigned char*)buffer.data(), 22+nBytes, i);
    if (checksum!=(unsigned char)buffer[i+22+nBytes]){
      printf("Checksums do not match - msg 0x%02x - calc 0x%02x\n", (unsigned char)buffer[i+22+nBytes], checksum);
      buffer.remove(0,i+23+nBytes);
      continue;
    }

//    printf("Checksums match\n");
    //        memcpy(&data,buffer.data()[i+22],sizeof(nBytes));
//    printf("Byte No: ");
//    for (j=0;j<nBytes;j++) printf("%04i ", j);
//    printf("\n");   
//    printf("  data = ");
//    for (j=0;j<nBytes;j++) printf("0x%02x ", (unsigned char)buffer.data()[i+j+22]);
//    printf("\n");
   //   printf("String = %s", QString(data).toAscii().data());
    if (opCode==0) printf("No-Op requested\n");
    if (opCode==17){
      vData=vData.fromByteArray(buffer.mid(i+22,nBytes));
//      FILE *dumpFile;
//      dumpFile=fopen("dumpFile","wb");
//      fwrite(buffer.data(), buffer.count(), 1, dumpFile);
//      fclose(dumpFile);
//      vData.print();
      tmpData.time=msgDateTime;
      tmpData.position.x=vData.longitude;
      tmpData.position.y=vData.latitude;
      tmpData.position.z=0.;
      tmpData.velocity.x=vData.speedOverGround;
      tmpData.velocity.y=0.;
      tmpData.velocity.z=0.;
      tmpData.attitude.x=vData.roll;
      tmpData.attitude.y=vData.pitch;
      tmpData.attitude.z=vData.heading;
      tmpData.track=vData.track;
      tmpData.speed=vData.speedOverGround;
      tmpData.hDOP=vData.hdop;
      tmpData.vDOP=vData.vdop;
      tmpData.mDOP=vData.mdop;
      emit newTelemetryDataPoint(tmpData);
    }
    // Clear buffer up to the end of this message
    buffer.remove(0,i+23+nBytes);
  }
}

QWidget* aydpPlugin::settingsPanel(){
  return settings.guiPanel;
}

void aydpPlugin::storeSettings(){
  settings.storeGUIValues(); 
}

void aydpPlugin::readData(int sckId){
  int n, i, mType, mLength;
  int start=-1;
  int nData;
  float msgData[1024];
  char grab[4096];
  struct timeval msgTime;
  
  n = read(sckId,grab,4096);
  buffer.append(QByteArray(grab,n));
/*  
  printf("Input: ");
  for (i=0;i<buffer.count();i++){
    printf("0x%02x ",(unsigned char)buffer.at(i));
  }
  printf("\n");
*/  
  for (i=0;i<buffer.count();i++){
    if ((unsigned char)buffer.at(i)==(unsigned char)0xff && start<0){
      start=i;
      break;
    }
  }
  
  if (start>0) buffer.remove(0,start);
/*  
  printf("Clipped: ");
  for (i=0;i<buffer.count();i++){
    printf("0x%02x ",(unsigned char)buffer.at(i));
  }
  printf("\n");
*/  
//  mType=protocol.parseFloatMessage((unsigned char*)buffer.data(), buffer.count(), &mLength, &msgTime, &nData, msgData);
//  printf("Message Type = %i\n", mType);
//  printf("Message Length = %i bytes\n", mLength);
  if (mType>=0){
//    printf("Message Data:\n");
    printf("Time     = %li (secs)\n",msgTime.tv_sec);
    printf("Time     = %li (u_sec)\n",msgTime.tv_usec);
  
    for (i=0;i<nData;i++) printf("  %f\n", msgData[0]);
    buffer.remove(0,mLength);
  }
  if (mType==-3) buffer.remove(0,1);
}

unsigned char aydpPlugin::createChecksum(unsigned char msg[], int msglen, int offset){
  int i;
  unsigned char checksum;
  checksum=msg[0];
  for (i=1;i<msglen;i++) checksum^=msg[i+offset];
//  printf("Checksum = 0x%02x    %i\n",checksum, checksum);
  return checksum;
}