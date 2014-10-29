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
#include "SerialIO_linux.h"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>

SerialIO::SerialIO(QObject *parent) : QObject(parent)
{
  int i;
  printf("Initialising OpenPilot::SerialIO\n");
  fd=-1;
  bufferSizeLimit=4*1024;  // 4kBytes
  
  portSet.setValue("/serialio/baud",9600);
  portSet.setValue("/serialio/databits",8);

//  currentIO.c_iflag=0;
/*
  BRKINT - Signal interrupt on break.
  ICRNL  - Map CR to NL on input.
  IGNBRK - Ignore break condition.
  IGNCR  - Ignore CR.
  IGNPAR - Ignore characters with parity errors.
  INLCR  - Map NL to CR on input.
  INPCK  - Enable input parity check.
  ISTRIP - Strip character.
  IUCLC  - Map upper case to lower case on input. (LEGACY)
  IXANY  - Enable any character to restart output.
  IXOFF  - Disable start/stop input control.
  IXON   - Enable start/stop input control.
  PARMRK - Mark parity errors.
*/

//  currentIO.c_oflag=0;
/*
  OPOST  - Perform output processing.
  OLCUC  - Map lower case to upper on output. (LEGACY)
  ONLCR  - Map NL to CR-NL on output.
  OCRNL  - Map CR to NL on output.
  ONOCR  - No CR output at column 0.
  ONLRET - NL performs CR function.
  OFILL  - Use fill characters for delay.
  OFDEL  - Fill is DEL, else NUL.
  NLDLY  - Select newline delays:
  NL0    - Newline character type 0
  NL1    - Newline character type 1.
  CRDLY  - Select carriage-return delays:
  CR0    - Carriage-return delay type 0
  CR1    - Carriage-return delay type 1
  CR2    - Carriage-return delay type 2
  CR3    - Carriage-return delay type 3.
  TABDLY - Select horizontal-tab delays:
  TAB0   - Horizontal-tab delay type 0
  TAB1   - Horizontal-tab delay type 1
  TAB2   - Horizontal-tab delay type 2.
  TAB3   - Expand tabs to spaces.
  BSDLY  - Select backspace delays:
  BS0    - Backspace-delay type 0
  BS1    - Backspace-delay type 1.
  VTDLY  - Select vertical-tab delays:
  VT0    - Vertical-tab delay type 0
  VT1    - Vertical-tab delay type 1.
  FFDLY  - Select form-feed delays:
  FF0    - Form-feed delay type 0
  FF1    - Form-feed delay type 1.
*/

//  currentIO.c_cflag=CS8;
/*
  CLOCAL - Ignore modem status lines.
  CREAD  - Enable receiver.
  CSIZE  - Number of bits transmitted or received per byte:
    CS5  - 5 bits
    CS6  - 6 bits
    CS7  - 7 bits
    CS8  - 8 bits.
  CSTOPB - Send two stop bits, else one.
  HUPCL  - Hang up on last close.
  PARENB - Parity enable.
  PARODD - Odd parity, else even.
*/

//  currentIO.c_lflag=0;
/*
  ECHO   - Enable echo.
  ECHOE  - Echo ERASE as an error correcting backspace.
  ECHOK  - Echo KILL.
  ECHONL - Echo <newline>.
  ICANON - Canonical input (erase and kill processing).
  IEXTEN - Enable extended (implementation-dependent) functions.
  ISIG   - Enable signals.
  NOFLSH - Disable flush after interrupt, quit or suspend.
  TOSTOP - Send SIGTTOU for background output.
  XCASE  - Canonical upper/lower presentation. (LEGACY)
*/

  // currentIO.c_cc[NCCS];
/*
Canonical   Non-canonical
  Mode          Mode           Description
  VEOF                        EOF character
  VEOL                        EOL character
 VERASE                      ERASE character
 VINTR         VINTR          INTR character
 VKILL                        KILL character
               VMIN             MIN value
 VQUIT         VQUIT          QUIT character
 VSUSP         VSUSP           SUSP character
               VTIME            TIME value
 VSTART        VSTART         START character
 VSTOP         VSTOP           STOP character
*/
//  currentIO.c_ispeed=B9600;
//  currentIO.c_ospeed=B9600;
/*
      B0 -  Hang up         B600  -   600 baud
     B50 -  50 baud         B1200 -  1200 baud
     B75 -  75 baud         B1800 -  1800 baud
    B110 - 110 baud         B2400 -  2400 baud
    B134 - 134.5 baud       B4800 -  4800 baud
    B150 - 150 baud         B9600 -  9600 baud
    B200 - 200 baud        B19200 - 19200 baud
    B300 - 300 baud        B38400 - 38400 baud
*/
}

void SerialIO::readSettings(QDomNode root){
  QDomNode node;
  QDomElement element;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="device") setDevice(element.text());
    node=node.nextSibling();
  }
}

int SerialIO::open(){
  printf("SerialIO::open() - %s - Unix Implementation\n", dev.toAscii().data());
  if (fd>0){
    printf("SerialIO :: Device already open\n");
    return 0;
  }
  fd=::open( device().toAscii().data() , O_RDWR | O_NDELAY);
  if (fd<0){
    printf("SerialIO :: Failed to open device\n");
    return 6;
  }
  if (!isatty(fd)){
    printf("SerialIO :: Device is not a TTY\n");
    return 6;
  }
  setattr();
  notifier=new QSocketNotifier(fd, QSocketNotifier::Read, this);
  connect(notifier, SIGNAL(activated(int)), this, SLOT(getData(int)));
  return 0;
}

void SerialIO::setattr(){
  struct termios currentIO;
  speed_t _baud=B9600;
  int state;
  if (fd<0){
    printf("SerialIO :: Cannot set attributes when no device is open\n");
    return;
  }
  
  if (tcgetattr(fd, &currentIO) == -1) printf("SerialIO :: Could not get attributes\n");
  
  cfmakeraw(&currentIO);
  currentIO.c_cflag |= CLOCAL | CREAD;
  if (baud()==    0) _baud=B0;
  if (baud()==   50) _baud=B50;
  if (baud()==   75) _baud=B75;
  if (baud()==  110) _baud=B110;
  if (baud()==  134) _baud=B134;
  if (baud()==  150) _baud=B150;
  if (baud()==  200) _baud=B200;
  if (baud()==  300) _baud=B300;
  if (baud()==  600) _baud=B600;
  if (baud()== 1200) _baud=B1200;
  if (baud()== 1800) _baud=B1800;
  if (baud()== 2400) _baud=B2400;
  if (baud()== 4800) _baud=B4800;
  if (baud()== 9600) _baud=B9600;
  if (baud()==19200) _baud=B19200;
  if (baud()==38400) _baud=B38400;
  if (baud()==57600) _baud=B57600;
  if (baud()==115200) _baud=B115200;
  if (baud()==230400) _baud=B230400; 
  cfsetospeed(&currentIO, (speed_t)_baud);
  cfsetispeed(&currentIO, (speed_t)_baud);
/*
  CLOCAL - Ignore modem status lines.
  CREAD  - Enable receiver.
  CSIZE  - Number of bits transmitted or received per byte:
    CS5  - 5 bits
    CS6  - 6 bits
    CS7  - 7 bits
    CS8  - 8 bits.
  CSTOPB - Send two stop bits, else one.
  HUPCL  - Hang up on last close.
  PARENB - Parity enable.
  PARODD - Odd parity, else even.
*/
  if (dataBits()==5) currentIO.c_cflag |= CS5;
  if (dataBits()==6) currentIO.c_cflag |= CS6;
  if (dataBits()==7) currentIO.c_cflag |= CS7;
  if (dataBits()==8) currentIO.c_cflag |= CS8;

/*
  PARENB - Parity enable.
  PARODD - Odd parity, else even.
*/
  if (parityEn()) currentIO.c_cflag |= PARENB;
  if (parityOdd()) currentIO.c_cflag |= PARODD;
  if (stopBits()==2) currentIO.c_cflag |= CSTOPB;
  if (XIN()) currentIO.c_iflag |= IXOFF;
  if (XOUT()) currentIO.c_iflag |= IXON;
/*
  IXANY  - Enable any character to restart output.
  IXOFF  - Enable start/stop input control.
  IXON   - Enable start/stop output control.
*/

  tcsetattr(fd, TCSANOW, &currentIO);

  if (!RTS()){  
    printf("Disabling RTS\n");
    if (ioctl(fd, TIOCMGET, &state) == -1) printf("SerialIO:: RTS IOCTL Failed\n");
    state &= ~TIOCM_RTS; // Turn off RTS
    if (ioctl(fd, TIOCMSET, &state) == -1) printf("SerialIO:: RTS IOCTL Failed\n");
  }
  
  // Pull down DTR briefly to reset arduino.
  // Arduino-specific code...
    printf("Pulling DTR\n");
    if (ioctl(fd, TIOCMGET, &state) == -1) printf("SerialIO:: RTS IOCTL Failed\n");
    state &= ~TIOCM_DTR; // Turn off DTR
    if (ioctl(fd, TIOCMSET, &state) == -1) printf("SerialIO:: RTS IOCTL Failed\n");
    state |= TIOCM_DTR; // Turn on DTR
    if (ioctl(fd, TIOCMSET, &state) == -1) printf("SerialIO:: RTS IOCTL Failed\n");
  tcflush(fd, TCIFLUSH);
}

void SerialIO::close(){
  printf("SerialIO::close()\n");
  if (fd<0) return;
  if (notifier->isEnabled()){
    disconnect(notifier, SIGNAL(activated(int)), this, SLOT(getData(int)));
    delete notifier;
  }
  ::close(fd);
  fd=-1;
}

void SerialIO::send(QString string){
  char *temp;
  string+="\n\r";
  send(string.toAscii().data());
}

void SerialIO::send(char *string){
  int i;
  if (fd<0) return;
  ::write(fd,string,strlen(string));
}

void SerialIO::getData(){ getData(fd); }

void SerialIO::getData(int nfd){
//  printf("SerialIO::getData()\n");
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
/*
  if (buffer.size()>bufferSizeLimit){
    buffer.erase(buffer.begin(), buffer.end()-bufferSizeLimit);
  }
  */
  Sentence=QString(buffer);
  list1=Sentence.split("$");
  for (i=0;i<list1.count();i++) emit rawString(list1[i]);
  buffer.clear();
  buffer.append(list1[list1.count()-1]);
  emit newData();
}

void SerialIO::setDevice(QString var){
  close();
  dev=var;
}

QString SerialIO::device(){ return dev; }

void SerialIO::setBaud(int brt){
  int diff, mindiff=38500, idx, i, baudArr[19];
  baudArr[ 0]=    0;  baudArr[ 1]=   50;
  baudArr[ 2]=   75;  baudArr[ 3]=  110;
  baudArr[ 4]=  134;  baudArr[ 5]=  150;
  baudArr[ 6]=  200;  baudArr[ 7]=  300;
  baudArr[ 8]=  600;  baudArr[ 9]= 1200;
  baudArr[10]= 1800;  baudArr[11]= 2400;
  baudArr[12]= 4800;  baudArr[13]= 9600;
  baudArr[14]=19200;  baudArr[15]=38400;
  baudArr[16]=57600;  baudArr[17]=115200;
  baudArr[18]=230400;
  
  for (i=0;i<19;i++){
    diff=abs(baudArr[i]-brt);
    if (diff<mindiff){
      mindiff=diff;
      idx=i;
    }
  }

  portSet.setValue("/serialio/baud",baudArr[idx]);
}

int SerialIO::baud(){
  return portSet.value("/serialio/baud").toInt();
}

void SerialIO::setDataBits(int db){
  if (db<5) db=5;
  if (db>8) db=8;
  portSet.setValue("/serialio/databits",db);
}

int SerialIO::dataBits(){
  return portSet.value("/serialio/databits").toInt();
}

void SerialIO::setParityEn(bool par){
  portSet.setValue("/serialio/EnableParity",par);
}

bool SerialIO::parityEn(){
  return portSet.value("/serialio/EnableParity").toBool();
}

void SerialIO::setParityOdd(bool par){
  portSet.setValue("/serialio/OddParity",par);
}

bool SerialIO::parityOdd(){
  return portSet.value("/serialio/OddParity").toBool();
}

void SerialIO::setStopBits(int stop){
  if (stop<1) stop=1;
  if (stop>2) stop=2;
  portSet.setValue("/serialio/stopbits",stop);
}

int SerialIO::stopBits(){
  return portSet.value("/serialio/stopbits").toInt();
}

void SerialIO::setXIN(bool xin){
  portSet.setValue("/serialio/xin",xin);
}

bool SerialIO::XIN(){
  return portSet.value("/serialio/xin").toBool();
}

void SerialIO::setXOUT(bool xout){
  portSet.setValue("/serialio/xout",xout);
}

bool SerialIO::XOUT(){
  return portSet.value("/serialio/xout").toBool();
}

void SerialIO::setRTS(bool rts){
  portSet.setValue("/serialio/rts",rts);
}

bool SerialIO::RTS(){
  return portSet.value("/serialio/rts").toBool();
}