#include "joystick.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <sys/stat.h>

joystick::joystick(QObject *parent) : QThread(parent){
}

void joystick::run(){
  connTimer = new QTimer(); connTimer->setInterval(2000);
  connect(connTimer, SIGNAL(timeout()), this, SLOT(openDevice()));
  
  checkTimer = new QTimer(); checkTimer->setInterval(1000);
  connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkDevice()));
  cState=false; emit connState(cState);
  connTimer->start();
  checkTimer->start();
  openDevice();
  exec();
}

void joystick::checkDevice(){
  struct stat info;
  
  if (0!=stat(device.toAscii().data(), &info)){
    if (cState!=false){
      close(fd);
      disconnect(notifier);
      delete notifier;
      cState=false; emit connState(cState);
      connTimer->start();
    }
  }
}

void joystick::setDevice(QString devName){
  device=devName;
}

bool joystick::openDevice(){
  int i;
  char c_name[80];
  if (cState==true) return true;
//  printf("Attempting to open device\n");
  cState=false; emit connState(cState);
  fd=open(device.toAscii().data(), O_RDONLY);
  if (fd<1) return false;
  
  
  nAxes=0; i=0;
  while(nAxes<=0 || nAxes>100){
    ioctl( fd, JSIOCGAXES, &nAxes );
    printf("    Axes: %d\n", nAxes);
    if (i>10){
      printf("Could not accurately determine number of axes\n");
      close(fd);
      return false;
    }
    i++;
  }
  
  nButtons=0; i=0;
  while(nButtons<=0 || nButtons>100){
    ioctl( fd, JSIOCGBUTTONS, &nButtons );
    printf(" Buttons: %d\n", nButtons);
    if (i>10){
      printf("Could not accurately determine number of axes\n");
      close(fd);
      return false;
    }
    i++;
  }
  connTimer->stop();
  
  ioctl( fd, JSIOCGNAME(80), &c_name ); name=c_name;
  printf("Joystick:\n");
  printf("    Name: %s\n", c_name);
  printf("    Axes: %d\n", nAxes);
  printf(" Buttons: %d\n", nButtons);
  
  notifier = new QSocketNotifier( fd, QSocketNotifier::Read );
  connect(notifier, SIGNAL(activated(int)), this, SLOT(readData()), Qt::DirectConnection);
  cState=true; emit connState(cState);
  emit deviceInfo(name, nAxes, nButtons);
  lastData=clock();
  return false;
}

bool joystick::readData(){
  double cal;
  struct js_event js;
  
//  printf("Grabbing data\n");
  if (sizeof(struct js_event)==read(fd, &js, sizeof(struct js_event))){  
    if ((js.type & ~JS_EVENT_INIT) == JS_EVENT_AXIS){
      cal=((double)js.value+32767.)/(2.*32767.)*100.;
      emit axis(js.number, cal);
//      printf("Axis %i\tValue %i\tCal %lf\n", js.number, js.value, cal);
      return true;
    }
    
    if ((js.type & ~JS_EVENT_INIT) == JS_EVENT_BUTTON){
//      emit button(js.number, js.value);
//      printf("Button %i\tValue %i\n", js.number, js.value);
      lastData=clock();
      return true;
    }
  }else{
    close(fd);
    connTimer->start();
    cState=false; emit connState(cState);
    return false;
  }
}