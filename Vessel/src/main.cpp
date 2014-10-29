#include <QCoreApplication>
#include <QtXml>
#include "dataStore.h"
#include "dataCollector.h"
#include "imuReader.h"
#include "maestro.h"
#include "pidControl.h"
#include "nmea.h"
#include "commsLink.h"

int main(int argc, char * argv[]){
/*
 * For testing Comms Link on PC only.

  dataStore vesselData;
  commsLink *cLink;
  
  QCoreApplication app(argc,argv);
  cLink= new commsLink(0, &vesselData);
  cLink->startServer();
*/  
  int i;
  dataStore vesselData;
//  aydpCommsProtocol commsProto;
  QList<dataCollector*> input;
  QCoreApplication app(argc,argv);
  logOutput *log = new logOutput();
  maestro *output = new maestro();
  
//  commsProto.registerFloat("Roll Angle", &vesselData.roll);  
//  commsProto.registerFloat("Pitch Angle", &vesselData.pitch);  
//  commsProto.registerFloat("Heading", &vesselData.heading);  
  
  log->setFileName("AYDP_LogFile.csv");
  vesselData.setupLogOutput(log);
        
  input.append(new imuReader(0, &vesselData));
  input.append(new NMEA(0, &vesselData));
  // Test Servo output
  
  output->grabDevice("00009132");
  output->channel[0].coefficient.append(1500);
  output->channel[0].coefficient.append(-500/45);
  output->channel[0].bounded=true;
  output->channel[0].lowerBound=-30;
  output->channel[0].upperBound=30;
  log->flt.append(&output->channel[0].input); log->fltHeader.append("Rudder Demand");
  
  output->channel[2].coefficient.append(0);
  output->channel[2].coefficient.append(1);
  log->flt.append(&output->channel[2].input); log->fltHeader.append("MainSail Demand");
    
  output->channel[3].coefficient.append(1000);
  output->channel[3].coefficient.append(1000/250.);
  log->flt.append(&output->channel[3].input); log->fltHeader.append("Jib Demand");
  
  // Register the output channels with comms...
//  commsProto.registerFloat("Rudder Demand", &output->channel[0].input);  
//  commsProto.registerFloat("MainSail Demand", &output->channel[2].input);  
//  commsProto.registerFloat("Jib Demand", &output->channel[3].input);  
//  commsProto.listRegisteredVariables();
  
  output->orderPosition(0, 0.);
  output->orderPosition(2, 4000.);
  output->orderPosition(3, 0.);
  
  // Create PID heading autopilot
  logOutput *apLog = new logOutput();
  pidControl *headAP = new pidControl();
  
  apLog->setFileName("AYDP_HeadingAP_LogFile.csv");
  headAP->setObjectName("headingAP");
  
//  headAP->setCoefficients(2, .1, .25);
  headAP->setChannel(0);
  headAP->setSignal(&vesselData.heading);
  headAP->setDerivative(&vesselData.headingRate);
  headAP->setIntegralLimit(10);
  headAP->setTarget(0);
  headAP->setupLogOutput(apLog);
  
  QObject::connect(headAP, SIGNAL(control(int,float)), output, SLOT(orderPosition(int,float)));
  
  // Read settings file...
  int erl, erc;
  QDomNode node, node2;
  QDomElement root, element, element2;
  QString errMsg, fileName="settings.xml";
  QFile file;
  
  file.setFileName(fileName);
  if (!file.open( QIODevice::ReadOnly )){
    printf("Could not open XML settings file - %s\n",fileName.toAscii().data());
    return 1;
  }

  QDomDocument doc( "sessionFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("Error at line %i, Column %i - %s\n", erl, erc,errMsg.toAscii().data());
    file.close();
    return 1;
  }
  file.close();

  root=doc.documentElement();
  if (root.tagName().toLower() != "aydp"){
    printf("This is not aa AYDP configuration file\n");
    return 1;
  }

  node=root.firstChild();
  while (!node.isNull()){
    headAP->readSettings(node);
    for (i=0;i<input.count();i++) input[i]->readSettings(node);
    node=node.nextSibling();
  }
  
  log->start();
  // Start input threads
  for (i=0;i<input.count();i++) input[i]->start();
  headAP->start();
  return app.exec();
}
