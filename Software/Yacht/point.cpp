#include "point.h"
#include <math.h>
point::point(){
  x=0; y=0;  
}

point::point(double px, double py){
  x=px; y=py;  
}

point point::operator+(point b){
  point tmp;
  tmp.x=x+b.x;
  tmp.y=y+b.y;
  return tmp;
}

point point::operator-(point b){
  point tmp;
  tmp.x=x-b.x;
  tmp.y=y-b.y;
  return tmp;
}

point point::operator/(double b){
  point tmp;
  tmp.x=x/b;
  tmp.y=y/b;
  return tmp;
}

point point::operator*(double b){
  point tmp;
  tmp.x=x*b;
  tmp.y=y*b;
  return tmp;
}

double point::mag(){
  double m;
  m=sqrt(x*x+y*y);
  return m;
}