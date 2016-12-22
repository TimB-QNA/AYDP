
#include "channel.h"


channel::channel(){
  lowLimit=1000;
  highLimit=2000;
  setPoint=1500;
  changed=false;
}

void channel::set(unsigned int val){
  changed=!(setPoint==val);
  setPoint=val;
}

unsigned int channel::value(){
  if (setPoint<lowLimit) return lowLimit;
  if (setPoint>highLimit) return highLimit;
  return setPoint;
}

