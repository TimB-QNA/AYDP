#ifndef POINT_H
  #define POINT_H
  
class point{
  public:
    point();
    point(double px, double py);
    point operator+(point b);
    point operator-(point b);
    point operator/(double b);
    point operator*(double b);
    double mag();
    
    double x, y;
};

#endif