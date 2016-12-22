// Widget to collect wind data and plot historical data on screen

#include "windData.h"
#include <sys/time.h>

windData::windData(QWidget *parent) : QWidget(parent){
  int i;
  QGridLayout *glay = new QGridLayout;
  
  direction = new gauge();
  direction->setMaximum(360);
  direction->setMinimum(0);
  direction->setMaximum(360);
  direction->setStartAngle(0);
  direction->setEndAngle(360);
  direction->setBorder(2);
  direction->setShowRanges(false);
  direction->setPlateType(1);
  direction->setTics(9);
  direction->setSubTics(4);
  direction->setLabel("Wind Direction");
  glay->addWidget(direction,0,0);
  
  speed = new gauge();
  speed->setMaximum(16);
  speed->setMinimum(0);
  speed->setStartAngle(230);
  speed->setEndAngle(495);
  speed->setBorder(2);
  speed->setSafeMin(0);
  speed->setSafeMax(5.0);
  speed->setWarnMin(5.0);
  speed->setWarnMax(10.0);
  speed->setDangerMin(10.0);
  speed->setDangerMax(16.0);
  speed->setShowRanges(true);
  speed->setTics(9);
  speed->setSubTics(4);
  speed->setLabel("Wind Speed");
  glay->addWidget(speed,1,0);
  
  spdGraph = new qt4gnuplot();
  spdGraph->setTitle("Wind Speed");
  spdGraph->setXLabel("Time");
  spdGraph->setYLabel("Speed (MPH)");
  spdGraph->setGrid(true);
  glay->addWidget(spdGraph,0,1,2,2);
  
  dirGraph = new qt4gnuplot();
  dirGraph->setTitle("Wind Direction");
  dirGraph->setXLabel("Time");
  dirGraph->setYLabel("Direction (deg)");
  dirGraph->setGrid(true);
  glay->addWidget(dirGraph,0,3,2,2);
  
  setLayout(glay);
  
  ioPort = new SerialIO();
//  ioPort->setDevice("/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A9O3FDPT-if00-port0");
  ioPort->setDevice("/dev/rfcomm5");
  ioPort->setBaud(115200);
  connect(ioPort, SIGNAL(newData()), this, SLOT(processData()));
  ioPort->open();
}

void windData::processData(){
  int i, start=-1, rVal;
  struct timeval msgTime;
//  float prevDir;
  float wSpd, wDir;
  float nSecs;
  QStringList graphScript;
  char line[4096];
  
  for (i=0;i<ioPort->buffer.size();i++){
    if (ioPort->buffer[i]==0xff && start<0){
 //     printf("[");
      start=i;
      break;
    }
  }
  
  if (start>0){
    ioPort->buffer.erase(ioPort->buffer.begin(),ioPort->buffer.begin()+start);
  }
  
//  for (i=0;i<ioPort->buffer.size();i++){
//    printf("0x%02x ",ioPort->buffer[i]);
//  }
//  printf("\n");
  
  if (start==0){
//    prevDir=windDirection.last();
    rVal=protocol.parseWindSpeedMessage(ioPort->buffer.data(), ioPort->buffer.size(), &msgTime, &wSpd);
    rVal=protocol.parseWindDirectionMessage(ioPort->buffer.data(), ioPort->buffer.size(), &msgTime, &wDir);
    if (rVal>0){
      ioPort->buffer.erase(ioPort->buffer.begin(),ioPort->buffer.begin()+rVal);
//      nSecs=msgTime.day*24.*3600.+msgTime.hour*3600.+msgTime.min*60.+msgTime.sec+msgTime.micro/1.e6;
//      time.append(nSecs);
//      windSpeed.append(wSpd);
//      windDirection.append(wDir);
//      if (time.count()>1200){
//        time.pop_front();
//        windSpeed.pop_front();
//        windDirection.pop_front();
//      }
//      printf("%f %f %f %f\n",nSecs, windSpeed, windDirection, windDirection-prevDir);
//      fprintf(stderr,"Day %i - %i:%i:%i.%f - Spd %f\n",msgTime.day, msgTime.hour, msgTime.min, msgTime.sec, msgTime.micro/1.e6, windSpeed);
/*
      // Draw speed graph...
      graphScript.append("plot '-' with lines notitle");
      for (i=0;i<windSpeed.count();i++){
        sprintf(line,"%lf\t%lf",time[i],windSpeed[i]); graphScript.append(line);
      }
      graphScript.append("e");
      spdGraph->plotgraph(graphScript);
      
      // Draw direction graph...
      graphScript.clear();
      graphScript.append("plot '-' with lines notitle");
      for (i=0;i<windDirection.count();i++){
        sprintf(line,"%lf\t%lf",time[i],windDirection[i]); graphScript.append(line);
      }
      graphScript.append("e");
      dirGraph->plotgraph(graphScript);
*/
    }
  }
  
  direction->setValue(windDirection.last());
  speed->setValue(windSpeed.last());
  
  
/*
  rVal=protocol.parseWindMessage(ioPort->buffer.data(), ioPort->buffer.size(), &msgTime, &windSpeed, &windDirection);
  if (rVal==2 || rVal==3){
    ioPort->buffer.erase(ioPort->buffer.begin(),ioPort->buffer.begin()+1);
  }
  printf("\n");
  if (ioPort->buffer.size()>100){
    FILE *dump;
    dump=fopen("dumpFile","wb");
    fwrite(ioPort->buffer.data(),1,ioPort->buffer.size(),dump);
    fclose(dump);
    exit(0);
  }
  */
}