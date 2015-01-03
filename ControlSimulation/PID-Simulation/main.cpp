#include "pidControl.h"

int main(int argc, char * argv[]){
  int i;
  double input=0;
  pidControl *headAP = new pidControl();
 
  headAP->readSettings(node);
  headAP->setIterationTime(1e-3);
  headAP->setCoefficients(1, .2, .5);
  headAP->setChannel(0);
  headAP->setIntegralLimit(0.001);
  headAP->setSignal(&signal);

  headAP->setTarget(10);
  
  headAP->controlFunction();
  printf("Control output=%lf\n",headAP->control());
}
