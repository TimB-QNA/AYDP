#include "flightgearReader.h"
#include <stdio.h>

flightgearReader::flightgearReader(QThread *parent, dataStore *vData) : dataCollector(parent,vData)
{
  fprintf(stderr,"Creating flightgearReader\n");
  setObjectName("flightgearReader");
  port=7000;
}

void flightgearReader::readSettings(QDomNode root){
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

void flightgearReader::run(){
  int pollRate=100;
  
// Connect.
  tcpServer = new QTcpServer(this);
  if (!tcpServer->listen(QHostAddress::Any, port)) {
    fprintf(stderr,"Unable to start the server: %s.\n", tcpServer->errorString().toAscii().data());
    return;
  }
  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connection()));
  fprintf(stderr,"Server is running on port %i.\n", tcpServer->serverPort());
  
  exec();
}

void flightgearReader::connection(){
  cSkt = tcpServer->nextPendingConnection();
  connect(cSkt, SIGNAL(readyRead()), this, SLOT(readTCPData()));
  lastMsg=QDateTime::currentDateTimeUtc();
}

void flightgearReader::readTCPData(){
  int i;
  float dt, uBody, vBody;
  float r2d=180./(4.*atan(1));
  QString data=cSkt->readAll();
  QStringList lines=data.split("\n");
  QStringList elements;
  QDateTime now=QDateTime::currentDateTimeUtc();
  dt=(float)lastMsg.msecsTo(now)/1000.;
  lastMsg=now;
  for (i=0;i<lines.count();i++){
    lines[i]=lines[i].trimmed();
//    printf("Line %i : %s\n", i, lines[i].toAscii().data());
    elements=lines[i].split("\t");
//    printf("%i Elements found\n", elements.count());
    if (elements.count()==12){
      vesselData->pitchRate=(elements[3].toFloat()-vesselData->pitch)/dt;
      vesselData->rollRate=(elements[4].toFloat()-vesselData->roll)/dt;
      vesselData->headingRate=(elements[5].toFloat()-vesselData->heading)/dt;
      
      vesselData->altitude  =elements[0].toFloat();
      vesselData->longitude =elements[1].toFloat();
      vesselData->latitude  =elements[2].toFloat();
      vesselData->pitch     =elements[3].toFloat();
      vesselData->roll      =elements[4].toFloat();
      vesselData->heading   =elements[5].toFloat();
      vesselData->track     =elements[6].toFloat();
      vesselData->airspeed  =elements[7].toFloat();
      vesselData->speedOverGround =elements[8].toFloat();
      vesselData->temperature =elements[9].toFloat();
      
      uBody=elements[10].toFloat();
      vBody=elements[11].toFloat();
      vesselData->sideslip = atan2(vBody,uBody)*r2d;
      emit newData();
    }
  }
}

/*
  float r2d=180./(4.*atan(1.));
  float newRoll, newPitch, newHeading;
  float deltaT;
  QDateTime newTime;
  RTIMU_DATA imuData;
  if (spoof){
    newRoll=0.;
    newPitch=0.;
    newHeading=0.;
  }else{
    while (imu->IMURead()) {
      imuData = imu->getIMUData();
//    printf("Reading\n");
    }
    newRoll=imuData.fusionPose.x()*r2d;
    newPitch=imuData.fusionPose.y()*r2d;
    newHeading=imuData.fusionPose.z()*r2d;
  }
  
  if (fabs(newRoll)>1e-6 && fabs(newPitch)>1e-6 && fabs(newHeading)>1e-6){
    newTime=QDateTime::currentDateTimeUtc();       // Calculate time step. Later versions of
    deltaT=(float)sampleTime.msecsTo(newTime)/1e3; // QT can do this with micro-seconds which would be nicer.
 
//    printf("delta t is %f mSec\n",deltaT*1e3);
    if (fabs(vesselData->roll)>1e-6 && fabs(vesselData->pitch)>1e-6 && fabs(vesselData->heading)>1e-6){
      vesselData->rollRate=(newRoll-vesselData->roll)/deltaT;
      vesselData->pitchRate=(newPitch-vesselData->pitch)/deltaT;
      vesselData->headingRate=(newHeading-vesselData->heading)/deltaT;
    }
    
    vesselData->roll=newRoll;
    vesselData->pitch=newPitch;
    vesselData->heading=newHeading;
    sampleTime=newTime;
//    printf("Roll: %lf\t\tPitch: %lf\t\tHeading: %lf\n", vesselData->roll, vesselData->pitch, vesselData->heading);
//    printf("RollRate: %lf\t\tPitchRate: %lf\t\tHeadingRate: %lf\n", vesselData->rollRate, vesselData->pitchRate, vesselData->headingRate); 
  }
}
*/