/*
    Description: Provide Serial data input for OpenPilot
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 February 2008
        License: GPLv3

Changelog:
    23 February 2008 - v0.1.0 alpha:
        First Release
*/


#include <QtCore>
#include <QLatin1String>
#include <qdom.h>
#include <QFile>
#include <ctype.h>
#include "gpsReader.h"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>

gpsReader::gpsReader(QThread *parent, dataStore *vData) : dataCollector(parent,vData)
{
  fd=-1;
  bufferSizeLimit=4*1024;  // 4kBytes
  baud=9600;
  device="/dev/ttyAMA0";
}

void gpsReader::readSettings(QDomNode root){
  QDomNode node;
  QDomElement element;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="device") device=element.text();
    if (element.tagName().toLower()=="baud")   baud=element.text().toInt();
    node=node.nextSibling();
  }
}

void gpsReader::run(){
  struct termios currentIO;
  speed_t _baud;

  printf("Opening - %s\n", device.toLatin1().data());

  if (fd>0){
    printf("Device already open\n");
    return;
  }
  fd=::open( device.toLatin1().data() , O_RDWR | O_NDELAY);
  if (fd<0){
    printf("Failed to open device\n");
    return;
  }
  int state;

  if (tcgetattr(fd, &currentIO) == -1) printf("Could not get attributes\n");
  
  cfmakeraw(&currentIO);
  currentIO.c_cflag |= CLOCAL | CREAD;
  if (baud==    0) _baud=B0;
  if (baud==   50) _baud=B50;
  if (baud==   75) _baud=B75;
  if (baud==  110) _baud=B110;
  if (baud==  134) _baud=B134;
  if (baud==  150) _baud=B150;
  if (baud==  200) _baud=B200;
  if (baud==  300) _baud=B300;
  if (baud==  600) _baud=B600;
  if (baud== 1200) _baud=B1200;
  if (baud== 1800) _baud=B1800;
  if (baud== 2400) _baud=B2400;
  if (baud== 4800) _baud=B4800;
  if (baud== 9600) _baud=B9600;
  if (baud==19200) _baud=B19200;
  if (baud==38400) _baud=B38400;
  if (baud==57600) _baud=B57600;
  if (baud==115200) _baud=B115200;
  if (baud==230400) _baud=B230400;

  cfsetospeed(&currentIO, (speed_t)_baud);
  cfsetispeed(&currentIO, (speed_t)_baud);

  tcsetattr(fd, TCSANOW, &currentIO);

  tcflush(fd, TCIFLUSH);

  notifier=new QSocketNotifier(fd, QSocketNotifier::Read, this);
  connect(notifier, SIGNAL(activated(int)), this, SLOT(getData(int)));
  
  exec();
}

void gpsReader::close(){
  printf("Close\n");
  if (fd<0) return;
  if (notifier){
    if (notifier->isEnabled()){
      disconnect(notifier, SIGNAL(activated(int)), this, SLOT(getData(int)));
      delete notifier;
    }
  }
  ::close(fd);
  fd=-1;
}

void gpsReader::getData(int nfd){
  int bytesRead=0, inBuffSize=4096, i;
  QString Sentence;
  QStringList list1;
  unsigned char byteData[inBuffSize];

  for (i=0;i<inBuffSize;i++) byteData[i]='\0';

  if (fd!=nfd) return;
  bytesRead=::read(fd, byteData, inBuffSize);
  
  for (i=0;i<bytesRead;i++){
    buffer.append(byteData[i]);
  }

  if (buffer.size()>bufferSizeLimit){
    buffer.remove(0, buffer.count()-bufferSizeLimit);
  }
  
//  printf("Buffer = %s\n", buffer.data());
  
  while (extractSentence()<3){
  }
}

int gpsReader::extractSentence(){
  int i;
  int start=-1, end=-1;
  unsigned int messageChecksum, calculatedChecksum;
  
  printf("\n\nParsing buffer...\n");
  printf("Buffer = %s\n", buffer.data());
  
  printf("Finding first *\n");
  for (i=0;i<buffer.count();i++){
    if (buffer.at(i)=='*'){
      end=i;
      break;
    }
  }
  
  printf("End Position   : %i\n",end);
  
  printf("Working back to find $ sign\n");
  
  for (i=end;i>=0;i--){
    if (buffer.at(i)=='$'){
      start=i;
      break;
    }
  }
  
  printf("Start Position : %i\n",start);
  if (end==-1){
    // No end byte in message - likely to be incomplete, keep buffered data
    return 3;
  }
  if (start==-1){
    // Remove unwanted data where there is no start byte (including checksum)
    buffer.remove(0, end+3);
    return 2; // No start byte in message
  }
  
  if (buffer.count()<end+2) return 3; // Not enough data, keep buffered data
  
  // Extract sentence
  QByteArray sentence, chkSum;
  
  sentence=buffer.mid(start, end-start);
  chkSum=buffer.mid(end+1, 2);
  printf("Sentence: %s\n",sentence.data());
  printf("Checksum: %s\n",chkSum.data());

  sscanf(chkSum.data(), "%X", &messageChecksum);
  calculatedChecksum=checksum(sentence);
  
  printf("   Message Checksum 0x%02x\n", messageChecksum);
  printf("Calculated Checksum 0x%02x\n", calculatedChecksum);
  
  if (messageChecksum==calculatedChecksum) 
  
  buffer.remove(0, end+3);
  
  return 0;
}

/*!
 * This routine calculates the NMEA checksum. This is an XOR of all the ascii values of the
 * characters between $ and * in an NMEA0183 sentence.
 */
unsigned int gpsReader::checksum(QByteArray sentence){
  int i;
  unsigned int csum=0;
  
  if (sentence.size()<=1) return 0;
  for (i=0;i<sentence.size();i++){
    if (sentence.at(i)==QChar('*')) break;
    if (sentence.at(i)!=QChar('$')){
      if (csum==0){
        csum=sentence.at(i);
      }else{
        csum^=sentence.at(i);
      }
    }
  }
  
  return csum;
}