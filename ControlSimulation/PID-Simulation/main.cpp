#include "../../Vessel/src/pidControl.h"
#include <stdlib.h>

int main(int argc, char *argv[]){
  printf("Example of how to use a PID control loop\n");
  printf("outside of the autopilot system for simulation\n");
  printf("purposes. No effort has been spent on the response\n");
  printf("modelling; it is only an example!\n\n");
  printf("Press a key to close the plot\n");
  
  FILE *data, *script;
  float input=0, t, dt=10e-3, demand=0;
  pidControl *headAP = new pidControl();
 
  headAP->setIterationTime(dt);
  headAP->setCoefficients(-3, -8, .02);
  headAP->setChannel(0);
  headAP->setIntegralLimit(2);
  headAP->setSignal(&input);
      
  data=fopen("data.csv","w");
  script=fopen("script.gplt","w");
  
  fprintf(script,"#!/usr/bin/gnuplot\n");
  fprintf(script,"set grid\n");
  fprintf(script,"set yrange [-5:35]\n");
  fprintf(script,"plot 'data.csv' u 1:2 w l t 'Vessel', '' u 1:3 w l t 'Control', '' u 1:4 w l t 'Demand'\n");
  fprintf(script,"pause -1\n");
  
  for (t=0;t<5;t+=dt){
    if (t<1){
      demand=0;
    }else{
      demand=10;
    }
    headAP->setTarget(demand);
    
    headAP->controlFunction();
//    printf("Time=%2.6lf\tControl output=%lf\n",t,headAP->control());

    // Add some "dynamics" in...
    input+=headAP->control()*dt;

    fprintf(data,"%f\t%f\t%f\t%f\n",t,input,headAP->control(),demand);
  }
  fclose(script);
  fclose(data);
  
  system("gnuplot script.gplt");
}
