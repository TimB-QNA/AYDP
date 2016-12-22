#include "eventLoop.h"
#include <stdio.h>

eventLoop::eventLoop(QObject *parent) : QObject(parent)
{
  int i;

  navRoute.loadRouteFromKML("../../GISData/MyPlaces.kml", QString());
  
  cLink= new commsLink(0, &vesselData);
  cLink->startServer();

  mainScreen = new display(0, &vesselData);
  mainScreen->start();
  
  log = new logOutput();
//  output = new maestro();
  
  log->setFileName("AYDP_LogFile.csv");
  vesselData.setupLogOutput(log);
        
  input.append(new imuReader(0, &vesselData));
//  input.append(new NMEA(0, &vesselData));
  
  output->grabDevice("00009132");
  output->channel[0].coefficient.append(1500);
  output->channel[0].coefficient.append(-500/45);
  output->channel[0].bounded=true;
  output->channel[0].lowerBound=-30;
  output->channel[0].upperBound=30;
  log->flt.append(&output->channel[0].input); log->fltHeader.append("Rudder Demand");

// Output between 1000 and 2000 for full range. (i.e. 0 to 1)  
  output->channel[2].coefficient.append(1000);
  output->channel[2].coefficient.append(1000/250.);
  log->flt.append(&output->channel[2].input); log->fltHeader.append("MainSail Demand");
    
  output->channel[3].coefficient.append(1000);
  output->channel[3].coefficient.append(1000/250.);
  log->flt.append(&output->channel[3].input); log->fltHeader.append("Jib Demand");
  
  output->orderPosition(0, 0.);
  output->orderPosition(2, 0.);
  output->orderPosition(3, 0.);
  
  // Create PID heading autopilot
  apLog = new logOutput();
  headAP = new pidControl();
  
  apLog->setFileName("AYDP_HeadingAP_LogFile.csv");
  headAP->setObjectName("headingAP");
  
//  headAP->setCoefficients(2, .1, .25);
  headAP->setChannel(0);
  headAP->setSignal(&vesselData.heading);
  headAP->setDerivative(&vesselData.headingRate);
  headAP->setIntegralLimit(10);
  headAP->setTarget(31);
  headAP->setupLogOutput(apLog);
  
  cLink->registerData(0x0010, "Heading autopilot target", commsLink::float32, headAP->targetPointer());
  
  readSettings("settings.xml");
  
  printf("Starting log system\n");
  log->start();
  // Start input threads
  for (i=0;i<input.count();i++){
    printf("Starting %s\n",input[i]->objectName().toLatin1().data());
    input[i]->start();
  }
  printf("Starting heading autopilot\n");
//  headAP->start();
}

void eventLoop::readSettings(QString fileName){
  // Read settings file...
  int i;
  int erl, erc;
  QDomNode node, node2;
  QDomElement root, element, element2;
  QString errMsg;
  QFile file;
  
  file.setFileName(fileName);
  if (!file.open( QIODevice::ReadOnly )){
    printf("Could not open XML settings file - %s\n",fileName.toLatin1().data());
    return;
  }

  QDomDocument doc( "sessionFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("Error at line %i, Column %i - %s\n", erl, erc,errMsg.toLatin1().data());
    file.close();
    return;
  }
  file.close();

  root=doc.documentElement();
  if (root.tagName().toLower() != "aydp"){
    printf("This is not an AYDP configuration file\n");
    return;
  }

  node=root.firstChild();
  while (!node.isNull()){
    headAP->readSettings(node);
    for (i=0;i<input.count();i++) input[i]->readSettings(node);
    node=node.nextSibling();
  }
}

void eventLoop::enableOutput(){
  connect(headAP, SIGNAL(control(int,float)), output, SLOT(orderPosition(int,float)));
}

void eventLoop::directOutput(){
  disconnect(headAP, SIGNAL(control(int,float)));
}