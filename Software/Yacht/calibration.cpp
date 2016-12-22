#include "calibration.h"
#include <math.h>

calibration::calibration(){
  bounded=false;  
}

float calibration::calibrated(float in){
  int i;
  float sum=0;
  input=in;
  
  if (bounded){
    if (in<lowerBound) in=lowerBound;
    if (in>upperBound) in=upperBound;
  }
  
  if (coefficient.count()!=0){
    for (i=0;i<coefficient.count();i++){
      sum+=coefficient[i]*pow(in,i);
    }
  }else{
    sum=in;
  }
    
  return sum;
}
