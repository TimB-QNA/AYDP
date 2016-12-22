#include "aydpNetwork.h"
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

aydpNetwork::aydpNetwork(QObject *parent) : QObject(parent){
  statText="AYDP";
  statIndicator = new QLabel(QString("<html><font color='red'>")+statText+QString("</font></html>"));
  
  connTimer = new QTimer();
  connTimer->setInterval(5000);
  connTimer->setSingleShot(true);
  connect(connTimer, SIGNAL(timeout()), this, SLOT(checkForConnection()));
}

QObject* aydpNetwork::asQObject(){
  return this;  
}

QString aydpNetwork::pluginName(){
  return QString("aydpNetwork");
}

QString aydpNetwork::pluginDescription(){
  return QString("Allows communication with all AYDP systems.");
}

QString aydpNetwork::xmlRootTag(){
  return QString("aydpNet");
}

void aydpNetwork::readXML(QDomNode root){
  printf("Reading AYDP Network XML\n");
  settings.readXML(root);
  emit pluginRunning();
}

QStringList aydpNetwork::writeXML(){
  printf("Writing AYDP Network XML\n");
  return settings.writeXML();
}

QWidget* aydpNetwork::statusIndicator(){
  return statIndicator; 
}

void aydpNetwork::connectToPeer(){
  bool connOK=false;
  if (settings.deviceType==aydpSettings::network)   statText=QString("AYDP-Net");
  if (settings.deviceType==aydpSettings::serial)    statText=QString("AYDP-Ser");
  if (settings.deviceType==aydpSettings::bluetooth) statText=QString("AYDP-BT");
  statIndicator->setText(QString("<html><font color='yellow'>")+statText+QString("</font></html>"));
  
  connTimer->setInterval(settings.reconnectRate);
    
  if (settings.deviceType==aydpSettings::bluetooth){
    connOK=connectBluetooth();
  }
  
  if (connOK) statIndicator->setText(QString("<html><font color='green'>")+statText+QString("</font></html>"));
}

bool aydpNetwork::connectBluetooth(){
  struct sockaddr_rc addr;
  int status;

  printf("AYDP Network -- Connecting to Bluetooth device... Please wait.\n");
    
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

void aydpNetwork::disconnectFromPeer(){
  statIndicator->setText(QString("<html><font color='red'>")+statText+QString("</font></html>"));
}

QWidget* aydpNetwork::settingsPanel(){
  return settings.guiPanel;
}

void aydpNetwork::storeSettings(){
  settings.storeGUIValues(); 
}

void aydpNetwork::readData(int sckId){
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
  mType=protocol.parseFloatMessage((unsigned char*)buffer.data(), buffer.count(), &mLength, &msgTime, &nData, msgData);
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