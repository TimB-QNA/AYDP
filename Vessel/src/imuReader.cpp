#include "imuReader.h"
#include <stdio.h>

imuReader::imuReader(QThread *parent, dataStore *vData) : dataCollector(parent,vData)
{
  printf("Creating imuReader\n");
  setObjectName("imuReader");
}

void imuReader::readSettings(QDomNode root){
  QDomNode node;
  QDomElement element;
  
  if (root.toElement().tagName().toLower()!=objectName().toLower()) return;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="spoof") spoof=element.text().toLower().contains("true");
    if (element.tagName().toLower()=="settings") settingsFile=element.text();
    node=node.nextSibling();
  }
}

void imuReader::run(){
  int pollRate=100;
  
  if (!spoof){
    printf("Reading IMU settings\n");
    settings = new RTIMUSettings(settingsFile.toAscii().data());
    printf("Creating IMU interface\n");
    imu = RTIMU::createIMU(settings);
    printf("Initialising IMU\n");
    imu->IMUInit();
    pollRate=imu->IMUGetPollInterval();
  }
//  printf("Creating poll timer at %i ms\n",imu->IMUGetPollInterval());
  hwPollTimer = new QTimer();
  hwPollTimer->setInterval(pollRate);
  connect(hwPollTimer, SIGNAL(timeout()), this, SLOT(readIMU()));
  sampleTime=QDateTime::currentDateTimeUtc();
  hwPollTimer->start();
  
  exec();
}

void imuReader::readIMU(){
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