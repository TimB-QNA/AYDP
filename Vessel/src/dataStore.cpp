#include "dataStore.h"

dataStore::dataStore(){
  roll=0;
  pitch=0;
  heading=0;
  rollRate=0;
  pitchRate=0;
  headingRate=0;
  
// GPS
  latitude=0;
  longitude=0;
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
  log->dbl.append(&mdop);            log->dblHeader.append("MDOP");
  log->dbl.append(&hdop);            log->dblHeader.append("HDOP");
  log->dbl.append(&vdop);            log->dblHeader.append("VDOP");
}