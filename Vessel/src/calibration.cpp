#include "calibration.h"
#include <math.h>

calibration::calibration(){
  bounded=false;  
}

float calibration::calibrated(float in){
  int i;
  float sum=0;
  input=in;
  if (coefficient.count()!=0){
    for (i=0;i<coefficient.count();i++){
      sum+=coefficient[i]*pow(in,i);
    }
  }else{
    sum=in;
  }
  
  if (bounded){
    if (sum<lowerBound) sum=lowerBound;
    if (sum<upperBound) sum=upperBound;
  }
    
  return sum;
}
