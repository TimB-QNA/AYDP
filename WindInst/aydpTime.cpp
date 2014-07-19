#include "aydpTime.h"

aydpTime::aydpTime(){
  micro=0;
  sec=0;
  min=0;
  hour=0;
  day=0;
  year=114;
  deltaMicros=0;
  lastMicros=0;
}

void aydpTime::resetArduinoTime(unsigned long currentMicros){
  micro=0;
  sec=0;
  min=0;
  hour=0;
  day=0;
  year=114; // Reset to 2000 as reasonable value.
  deltaMicros=0;
  lastMicros=currentMicros;
}

void aydpTime::incrementByMicros(unsigned long currentMicros){
  deltaMicros=0;
  
  if (currentMicros != lastMicros) {
    // we have ticked over
    // calculate how many micros have gone past
    deltaMicros = currentMicros-lastMicros; // note this works even if micros() has rolled over back to 0
    lastMicros = currentMicros;
  }
  
  micro+=deltaMicros;
  
  while(micro>=1e6){
    micro-=1e6;
    sec++;
  }
  while(sec>59){
    min++;
    sec-=60;
  }
  while(min>59){
    hour++;
    min-=60;
  }
  while(hour>23){
    day++;
    hour-=24;
  }
  while(day>364){
    year++;
    day-=365;
  }
}
