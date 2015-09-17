#include "mainWindow.h"
#include <stdio.h>

mainWindow::mainWindow(QMainWindow *parent) : QMainWindow(parent)
{
  int i;
  QGridLayout *gridLayout = new QGridLayout();
//  setupAutopilot();
  
//  gridLayout->addWidget(rollAP,0,0);
  log = new logOutput();
  log->setFileName("AYDP_LogFile.csv");
  cds = new dataStore();
  cds->setupLogOutput(log);
  
  gds = new guiDataStore(cds);
  
  input.append(new flightgearReader(0, cds));
  connect(input.last(), SIGNAL(newData()), this, SLOT(newPlatformData()));
  
  setCentralWidget(gds);

  for (i=0;i<input.count();i++){
    printf("Starting %s\n",input[i]->objectName().toAscii().data());
    input[i]->start();
  }
  
  output = new flightgearWriter;
  txDock = new joystickStatusDock(this); addDockWidget(Qt::LeftDockWidgetArea, txDock);
  tx = new joystick;
  connect(tx, SIGNAL(axis(int,double)),            this,   SLOT(joystickControl(int, double)));
  connect(tx, SIGNAL(deviceInfo(QString,int,int)), txDock, SLOT(setDeviceInfo(QString,int,int)));
  connect(tx, SIGNAL(axis(int,double)),            txDock, SLOT(setAxis(int,double)));  
  tx->setDevice("/dev/input/js0");
  tx->start();
  
}

void mainWindow::setupAutopilot(){
  /*
  int i;
  
  mainScreen = new display(0, &vesselData);
  mainScreen->start();
  
  log = new logOutput();
  log->setFileName("AYDP_LogFile.csv");
  vesselData.setupLogOutput(log);
        
  input.append(new flightgearReader(0, &vesselData));
  connect(input.last(), SIGNAL(newData()), this, SLOT(newPlatformData()));
  output = new flightgearWriter;
  
  txDock = new joystickStatusDock(this); addDockWidget(Qt::LeftDockWidgetArea, txDock);
  tx = new joystick;
  connect(tx, SIGNAL(axis(int,double)),            this,   SLOT(joystickControl(int, double)));
  connect(tx, SIGNAL(deviceInfo(QString,int,int)), txDock, SLOT(setDeviceInfo(QString,int,int)));
  connect(tx, SIGNAL(axis(int,double)),            txDock, SLOT(setAxis(int,double)));  
  tx->setDevice("/dev/input/js0");
  tx->start();
  
  // Create PID roll angle autopilot
  rollAPLog = new logOutput();
  rollAP = new guiPidLoop();
  
  rollAPLog->setFileName("AYDP_RollAP_LogFile.csv");
  rollAP->setObjectName("RollAP");
  
  rollAP->setCoefficients(-1.5, -0.2, -0.05);
  rollAP->setChannel(1);
  rollAP->setSignal(&vesselData.roll);
  rollAP->setDerivative(&vesselData.rollRate);
  rollAP->setIntegralLimit(1.0);
  rollAP->setTarget(0);
  rollAP->setupLogOutput(rollAPLog);
  
  // Create PID heading autopilot
  headAPLog = new logOutput();
  headAP = new pidControl();
  
  headAPLog->setFileName("AYDP_HeadingAP_LogFile.csv");
  headAP->setObjectName("headingAP");
  

// Normal Flight mode values
//  headAP->setCoefficients(-3, -1, -0.25);
//  headAP->setSignal(&vesselData.sideslip);
//  headAP->setTarget(0);
//  headAP->setIntegralLimit(2);

// Takeoff heading based  
  headAP->setCoefficients(2, 0.5, 0.125);
  headAP->setSignal(&vesselData.heading);
//  headAP->setDerivative(&vesselData.headingRate);

//  headAP->setCoefficients(2, 0.5, 0.125);
//  headAP->setSignal(&vesselData.track);
  headAP->setTarget(265.6);
  headAP->setIntegralLimit(2);
  
  headAP->setChannel(3);
  headAP->setupLogOutput(headAPLog);
  
    // Create PID heading autopilot
  pitchAPLog = new logOutput();
  pitchAP = new pidControl();
  
  pitchAPLog->setFileName("AYDP_PitchAP_LogFile.csv");
  pitchAP->setObjectName("pitchAP");
  
  pitchAP->setCoefficients(-2, 0.0, -0.5);
  pitchAP->setChannel(0);
  pitchAP->setSignal(&vesselData.pitch);
  pitchAP->setDerivative(&vesselData.pitchRate);
  pitchAP->setIntegralLimit(5);
  pitchAP->setTarget(5);
  pitchAP->setupLogOutput(pitchAPLog);
  
  airspeedAPLog = new logOutput();
  airspeedAP = new pidControl();
  
  airspeedAPLog->setFileName("AYDP_airspeedAP_LogFile.csv");
  airspeedAP->setObjectName("airspeedAP");
  
  airspeedAP->setCoefficients(-0.5, -0.05, -0.0);
  airspeedAP->setChannel(2);
  airspeedAP->setSignal(&vesselData.airspeed);
//  airspeedAP->setDerivative(&vesselData.pitchRate);
  airspeedAP->setIntegralLimit(10);
  airspeedAP->setTarget(29);
  airspeedAP->setupLogOutput(airspeedAPLog);
  
  readSettings("settings.xml");
  
  printf("Starting log system\n");
  log->start();
  // Start input threads
  for (i=0;i<input.count();i++){
    printf("Starting %s\n",input[i]->objectName().toAscii().data());
    input[i]->start();
  }
  printf("Starting heading autopilot\n");
  rollAP->setup();
//  headAP->start();
//  pitchAP->start();
//  airspeedAP->start();
  
  connect(rollAP,  SIGNAL(control(int,float)), output, SLOT(orderPosition(int,float)));
  connect(headAP,  SIGNAL(control(int,float)), output, SLOT(orderPosition(int,float)));
  connect(pitchAP, SIGNAL(control(int,float)), output, SLOT(orderPosition(int,float)));
  connect(airspeedAP, SIGNAL(control(int,float)), output, SLOT(orderPosition(int,float)));
  */
}

void mainWindow::newPlatformData(){
//  if (cds->airspeed<15) headAP->setCoefficients(4, 0.1, 0.06);
//  if (cds->airspeed<20) headAP->setCoefficients(2, 0.2, 0.06);
//  if (cds->altitude>35) headAP->setCoefficients(1, 0.5, 0.125);
/*  
  if (cds->altitude>60){
    pitchAP->setSignal(&vesselData.altitude);
    pitchAP->setCoefficients(-0.5, 0.0, -0.0);
    pitchAP->setTarget(100);
    pitchAP->setupLogOutput(pitchAPLog);
  }
  */
}

void mainWindow::readSettings(QString fileName){
  // Read settings file...
  int i;
  int erl, erc;
  QDomNode node, node2;
  QDomElement root, element, element2;
  QString errMsg;
  QFile file;
  
  file.setFileName(fileName);
  if (!file.open( QIODevice::ReadOnly )){
    printf("Could not open XML settings file - %s\n",fileName.toAscii().data());
    return;
  }

  QDomDocument doc( "sessionFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("Error at line %i, Column %i - %s\n", erl, erc,errMsg.toAscii().data());
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
    rollAP->readSettings(node);
    for (i=0;i<input.count();i++) input[i]->readSettings(node);
    output->readSettings(node);
    node=node.nextSibling();
  }
}


void mainWindow::joystickControl(int chan, double value){
  // Permit elevator, throttle and rudder...
  // JSC 0 - Elevator
  // JSC 1 - Aileron
  // JSC 2 - Throttle
  // JSC 3 - Rudder
  // JSC 4 - Left Slider

  if (chan==2){
    value=1-value/100.;
  }else{
    value=(value-50.)/50.*35.;
  }
  
  if (chan<5){ // && chan!=0 && chan!=1 && chan!=2 && chan!=3){
    output->orderPosition(chan,value);
  }

/*  
  if (chan==5){
//    printf("Chan5 Value=%lf\n",value);
    if (value>0.2){
      printf("Using AP\n");
      rollAP->setActive(true);
      headAP->setActive(true);
      pitchAP->setActive(true);
      airspeedAP->setActive(true);
    }else{
      printf("Using Manual\n");
      rollAP->setActive(false);
      headAP->setActive(false);
      pitchAP->setActive(false);
      airspeedAP->setActive(false);
    }
  }
*/
//  if (chan==0 && !pitchAP->isActive()) output->orderPosition(chan,value);
//  if (chan==1 && !rollAP->isActive()) output->orderPosition(chan,value);
//  if (chan==2 && !airspeedAP->isActive()) output->orderPosition(chan,value);
//  if (chan==3 && !headAP->isActive()) output->orderPosition(chan,value);
}
 