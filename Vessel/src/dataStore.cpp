#include "dataStore.h"

dataStore::dataStore(){
  roll=0;
  pitch=0;
  heading=0;
  rollRate=0;
  pitchRate=0;
  headingRate=0;
  
// GPS
  latitude=0.0;
  longitude=0.0;
  track=0;
  speedOverGround=0;
  fixType=0;
  actSats=0;
  mdop=0.;
  hdop=0.;
  vdop=0.;
}

void dataStore::setupLogOutput(logOutput *log){
  log->flt.append(&roll);            log->fltHeader.append("Roll");
  log->flt.append(&pitch);           log->fltHeader.append("Pitch");
  log->flt.append(&heading);         log->fltHeader.append("Heading");
  log->flt.append(&rollRate);        log->fltHeader.append("Roll rate");
  log->flt.append(&pitchRate);       log->fltHeader.append("Pitch rate");
  log->flt.append(&headingRate);     log->fltHeader.append("Heading rate");

  // GPS Details
  log->flt.append(&track);           log->fltHeader.append("Track");
  log->flt.append(&speedOverGround); log->fltHeader.append("Speed over ground");
  log->dbl.append(&latitude);        log->dblHeader.append("Latitude");
  log->dbl.append(&longitude);       log->dblHeader.append("Longitude");
  log->integer.append(&fixType);     log->intHeader.append("GPS Fix Type");
  log->integer.append(&actSats);     log->intHeader.append("Active Satellites");
  log->flt.append(&mdop);            log->fltHeader.append("MDOP");
  log->flt.append(&hdop);            log->fltHeader.append("HDOP");
  log->flt.append(&vdop);            log->fltHeader.append("VDOP");
}

void dataStore::print(){
  printf("Data Store Contents:\n");
  printf("  Attitude:\n");
  printf("               Roll: %.3lf\n",roll);
  printf("              Pitch: %.3lf\n",pitch);
  printf("            Heading: %.3lf\n",heading);
  printf("          Roll Rate: %.3lf\n",rollRate);
  printf("         Pitch Rate: %.3lf\n",pitchRate);
  printf("       Heading Rate: %.3lf\n",headingRate);
  printf("  GPS:\n");
  printf("           Latitude: %.6lf\n",latitude);
  printf("          Longitude: %.6lf\n",longitude);
  printf("              Track: %.3lf\n",track);
  printf("  Speed Over Ground: %.3lf\n",speedOverGround);
  printf("           Fix Type: %i\n",fixType);
  printf("  Active Sattelites: %i\n",actSats);
  printf("           Mean DOP: %.3lf\n",mdop);
  printf("          Horiz DOP: %.3lf\n",hdop);
  printf("       Vertical DOP: %.3lf\n",vdop);
}

QByteArray dataStore::toByteArray(){
  size_t size;
  char buffer[80];
  QByteArray data;
  
  size=sizeof(float);  memcpy(buffer, &roll, size);            data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &pitch, size);           data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &heading, size);         data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &rollRate, size);        data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &pitchRate, size);       data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &headingRate, size);     data.append(buffer, size);
  
  size=sizeof(double); memcpy(buffer, &latitude, size);        data.append(buffer, size);
  size=sizeof(double); memcpy(buffer, &longitude, size);       data.append(buffer, size);

  size=sizeof(float);  memcpy(buffer, &track, size);           data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &speedOverGround, size); data.append(buffer, size);
  
  size=sizeof(int);    memcpy(buffer, &fixType, size);         data.append(buffer, size);
  size=sizeof(int);    memcpy(buffer, &actSats, size);         data.append(buffer, size);
  
  size=sizeof(float);  memcpy(buffer, &mdop, size);            data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &hdop, size);            data.append(buffer, size);
  size=sizeof(float);  memcpy(buffer, &vdop, size);            data.append(buffer, size);
  
  return data;
}

dataStore dataStore::fromByteArray(QByteArray input){
  int i;
  size_t size, sAcc;
  dataStore dStore;
  
//  printf("Roll: "); for (i=0;i<size;i++) printf("0x%02x ", (unsigned char)input.data()[i+sAcc]); printf("\n"); 
  
  sAcc=0;
  size=sizeof(float);  memcpy(&dStore.roll,            input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.pitch,           input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.heading,         input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.rollRate,        input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.pitchRate,       input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.headingRate,     input.data()+sAcc, size); sAcc+=size;
  size=sizeof(double); memcpy(&dStore.latitude,        input.data()+sAcc, size); sAcc+=size;
  size=sizeof(double); memcpy(&dStore.longitude,       input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.track,           input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.speedOverGround, input.data()+sAcc, size); sAcc+=size;
  size=sizeof(int);    memcpy(&dStore.fixType,         input.data()+sAcc, size); sAcc+=size;
  size=sizeof(int);    memcpy(&dStore.actSats,         input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.mdop,            input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.hdop,            input.data()+sAcc, size); sAcc+=size;
  size=sizeof(float);  memcpy(&dStore.vdop,            input.data()+sAcc, size); sAcc+=size;
  return dStore;
}