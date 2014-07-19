/*
    Description: Provide gauges for OpenPilot (Main Code)
         Author: Tim Brocklehurst
        Version: 0.2.0
           Date: 24 February 2008
        License: GPLv3

Changelog:
    09 December 2007 - v0.1.0 alpha:
        First Release
    24 February 2008 - v0.2.0
        Added two plates
        Set up foreground colour
*/


#include <QtGui>
#include <math.h>
#include "gauge.h"

gauge::gauge(QWidget *parent)
           : QWidget(parent)
{
  // Setup Variables
  PI=4.*atan(1.);
  g_antialias=true;
  g_type=0;
  a_type=0;
  s_tics=11;
  s_subtics=5;
  s_int=true;
  g_quality=120;
  g_border=0;
  startAng=30.;
  endAng=330.;
  chev_width=15.;
  min=0.;
  max=100.;
  setValue(13);
  g_textRad=.75;
  setDataScale(1.0);
  name="Demo Dial";
  g_suffix="deg";
  setWindowTitle(tr("Circular gauge"));
  g_showRanges=false;
  smin=0.; smax=30.; wmin=60.; wmax=80.; dmin=80.; dmax=100.; swdwidth=0.05;
  update();
}

void gauge::paintEvent(QPaintEvent *event){
  // This is the easiest way to implement drawing (and is actually fairly convenient!)
  centre=QPointF(width()/2., height()/2.);
  r=height()/2-g_border;
  if (height()>width()) r=width()/2-g_border;
  if (g_showRanges) draw_Ranges();
  if (g_type==0) draw_Plate0();
  if (g_type==1) draw_Plate1();
  if (g_type==2) draw_Plate2();
  if (g_type==100) draw_Plate100();
  if (g_type==101) draw_Plate101();
  if (g_type==102) draw_Plate102();
  if (g_type==103) draw_Plate103();

  if (a_type==0 && g_type<100) draw_Arrow0();
}

void gauge::draw_Ranges(){
  int i;
  double d, l;
  double x, y;
  double sang, eang;
  double ht, h=height()-20., ht2;
  QPointF range[100];
  QPointF p0, p1, p2;
  QPen pen;
  QBrush brush;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);
  if (g_type<100){
// Danger Range
  pen.setColor(QColor(255,0,0));
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(QColor(255,0,0));
  painter.setPen(pen);
  painter.setBrush(brush);
  sang=(dmin-min)/(max-min)*(endAng-startAng)+startAng;
  eang=(dmax-min)/(max-min)*(endAng-startAng)+startAng;
  for (i=0;i<50;i++){
    l=(double)i/49.;
    d=(eang-sang)*l+sang;
    x=sin(d*PI/180.)*r;
    y=-cos(d*PI/180.)*r;
    range[i]=centre+QPointF(x,y);
  }
  for (i=50;i<100;i++){
    l=(double)(i-50)/49.;
    d=(eang-sang)*(1.-l)+sang;
    x=sin(d*PI/180.)*(r*(1.-swdwidth));
    y=-cos(d*PI/180.)*(r*(1.-swdwidth));
    range[i]=centre+QPointF(x,y);
  }
  painter.drawPolygon(range,100);


// Warning Range
  pen.setColor(QColor(255,255,0));
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(QColor(255,255,0));
  painter.setPen(pen);
  painter.setBrush(brush);
  sang=(wmin-min)/(max-min)*(endAng-startAng)+startAng;
  eang=(wmax-min)/(max-min)*(endAng-startAng)+startAng;
  for (i=0;i<50;i++){
    l=(double)i/49.;
    d=(eang-sang)*l+sang;
    x=sin(d*PI/180.)*r;
    y=-cos(d*PI/180.)*r;
    range[i]=centre+QPointF(x,y);
  }
  for (i=50;i<100;i++){
    l=(double)(i-50)/49.;
    d=(eang-sang)*(1.-l)+sang;
    x=sin(d*PI/180.)*(r*(1.-swdwidth));
    y=-cos(d*PI/180.)*(r*(1.-swdwidth));
    range[i]=centre+QPointF(x,y);
  }
  painter.drawPolygon(range,100);
// Safe Range
  pen.setColor(QColor(0,255,0));
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(QColor(0,255,0));
  painter.setPen(pen);
  painter.setBrush(brush);

  sang=(smin-min)/(max-min)*(endAng-startAng)+startAng;
  eang=(smax-min)/(max-min)*(endAng-startAng)+startAng;
  for (i=0;i<50;i++){
    l=(double)i/49.;
    d=(eang-sang)*l+sang;
    x=sin(d*PI/180.)*r;
    y=-cos(d*PI/180.)*r;
    range[i]=centre+QPointF(x,y);
  }
  for (i=50;i<100;i++){
    l=(double)(i-50)/49.;
    d=(eang-sang)*(1.-l)+sang;
    x=sin(d*PI/180.)*(r*(1.-swdwidth));
    y=-cos(d*PI/180.)*(r*(1.-swdwidth));
    range[i]=centre+QPointF(x,y);
  }
  painter.drawPolygon(range,100);
  }
  if (g_type==100 || g_type==102){
    // Danger Range
    pen.setColor(QColor(255,0,0));
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,0,0));
    painter.setPen(pen);
    painter.setBrush(brush);
    ht=(dmin-min)/(max-min)*(double)(h-g_border*2);
    ht2=(dmax-min)/(max-min)*(double)(h-g_border*2);
    painter.drawRect(g_border,h-ht-g_border,width()-g_border*2,-(ht2-ht));

    // Warning Range
    pen.setColor(QColor(255,255,0));
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,255,0));
    painter.setPen(pen);
    painter.setBrush(brush);
    ht=(wmin-min)/(max-min)*(double)(h-g_border*2);
    ht2=(wmax-min)/(max-min)*(double)(h-g_border*2);
    painter.drawRect(g_border,h-ht-g_border,width()-g_border*2,-(ht2-ht));

    // Safe Range
    pen.setColor(QColor(0,255,0));
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,255,0));
    painter.setPen(pen);
    painter.setBrush(brush);
    ht=(smin-min)/(max-min)*(double)(h-g_border*2);
    ht2=(smax-min)/(max-min)*(double)(h-g_border*2);
    painter.drawRect(g_border,h-ht-g_border,width()-g_border*2,-(ht2-ht));
  }

}


void gauge::draw_Plate0(){
  int i;
  double d, l, h;
  double x, y, rt, cr;
  char text[10];
  QPointF *inner_chevron, *outer_chevron;
  QPointF p0, p1, p2;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);
  painter.setPen(g_color);
  // Draw an artistic gauge with centre at x0,y0
  painter.drawEllipse(centre.x()-r,centre.y()-r,r*2,r*2);

// Allocate memory for chevrons
  inner_chevron = new QPointF[g_quality];
  outer_chevron = new QPointF[g_quality];

// Chevron
  for (i=0;i<g_quality;i++){
    l=(double)i/(double)(g_quality-1);
    d=(endAng-startAng)*l+startAng;
    cr=0.6;
    if (endAng-startAng>360.) cr=.4+l*0.2;
    if (endAng-startAng<-360.) cr=.4-l*0.2;

    x=sin(d*PI/180.)*(cr*(double)r+l*chev_width/2.);
    y=-cos(d*PI/180.)*(cr*(double)r+l*chev_width/2.);
    outer_chevron[i]=centre+QPointF(x,y);

    x=sin(d*PI/180.)*(cr*(double)r-l*chev_width/2.);
    y=-cos(d*PI/180.)*(cr*(double)r-l*chev_width/2.);
    inner_chevron[i]=centre+QPointF(x,y);
  }
  painter.drawPolyline(inner_chevron,g_quality);
  painter.drawPolyline(outer_chevron,g_quality);
  painter.drawLine(inner_chevron[g_quality-1],outer_chevron[g_quality-1]);

  rt=.95;
  for (i=0;i<=s_subtics*(s_tics-1);i++){
    l=(double)i/(double)(s_subtics*(s_tics-1));
    d=(endAng-startAng)*l+startAng;

    x=sin(d*PI/180.)*(double)r;
    y=-cos(d*PI/180.)*(double)r;
    p1=QPointF(x,y);
    p2=p1*rt;
    painter.drawLine(centre+p1,centre+p2);
  }

  rt=.90;
  for (i=0;i<s_tics;i++){
    l=(double)i/(double)(s_tics-1);
    d=(endAng-startAng)*l+startAng;

    x=sin(d*PI/180.)*(double)r;
    y=-cos(d*PI/180.)*(double)r;
    p1=QPointF(x,y);
    p2=p1*rt;
    painter.drawLine(centre+p1,centre+p2);
  }

  for (i=0;i<s_tics;i++){
    l=(double)i/(double)(s_tics-1);
    d=(endAng-startAng)*l+startAng;
    if (!s_int) sprintf(text,"%4.1f",l*(max-min)+min);
    if (s_int){
      if (l*(max-min)+min>0.){
        sprintf(text,"%i",(int)(l*(max-min)+min+.5));
      }else{
        sprintf(text,"%i",(int)(l*(max-min)+min-.5));
      }
    }
    x=centre.x()+sin(d*PI/180.)*r*g_textRad;
    y=centre.y()-cos(d*PI/180.)*r*g_textRad;
    l=strlen(text)*7;
    h=14;
    if (endAng-360.!=startAng || i!=s_tics-1) painter.drawText((int)x-l/2,(int)y-h/2,l+2,h,Qt::AlignHCenter || Qt::AlignVCenter,text);
  }

  // We want the text forward of the dial background, but behind the arrow
  painter.drawText(centre.x()-50,centre.y()+r/4,100,20,Qt::AlignHCenter,name);
}


void gauge::draw_Plate1(){
  int i;
  double d, l, h;
  double x, y, rt, cr;
  char text[15]; //, digival[15];
  QPointF p0, p1, p2;

  QPainter painter(this);
  painter.setPen(g_color);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);

// Draw a gauge with centre at x0,y0
  painter.drawEllipse(centre.x()-r,centre.y()-r,r*2,r*2);

  rt=.95;
  for (i=0;i<=s_subtics*(s_tics-1);i++){
    l=(double)i/(double)(s_subtics*(s_tics-1));
    d=(endAng-startAng)*l+startAng;

    x=sin(d*PI/180.)*(double)r;
    y=-cos(d*PI/180.)*(double)r;
    p1=QPointF(x,y);
    p2=p1*rt;
    painter.drawLine(centre+p1,centre+p2);
  }

  rt=.90;
  for (i=0;i<s_tics;i++){
    l=(double)i/(double)(s_tics-1);
    d=(endAng-startAng)*l+startAng;

    x=sin(d*PI/180.)*(double)r;
    y=-cos(d*PI/180.)*(double)r;
    p1=QPointF(x,y);
    p2=p1*rt;
    painter.drawLine(centre+p1,centre+p2);
  }

  for (i=0;i<s_tics;i++){
    l=(double)i/(double)(s_tics-1);
    d=(endAng-startAng)*l+startAng;
    if (!s_int) sprintf(text,"%4.1f",l*(max-min)+min);
    if (s_int){
      if (l*(max-min)+min>0.){
        sprintf(text,"%i",(int)(l*(max-min)+min+.5));
      }else{
        sprintf(text,"%i",(int)(l*(max-min)+min-.5));
      }
    }
    x=centre.x()+sin(d*PI/180.)*r*g_textRad;
    y=centre.y()-cos(d*PI/180.)*r*g_textRad;
    l=strlen(text)*7;
    h=14;
    if (endAng-360.!=startAng || i!=s_tics-1) painter.drawText((int)x-l/2,(int)y-h/2,l+2,h,Qt::AlignHCenter || Qt::AlignVCenter,text);
  }

  // We want the text forward of the dial background, but behind the arrow
  painter.drawText(centre.x()-50,centre.y()+r/4,100,20,Qt::AlignHCenter,name);
  sprintf(text,"%4.1f ",g_value);
  painter.drawText(centre.x()-50,centre.y()+r/2,100,20,Qt::AlignHCenter,text+g_suffix);
}


void gauge::draw_Plate2(){
  int i;
  double d, l, h;
  double x, y, rt, cr;
  char text[15]; //, digival[15];
  QPointF p0, p1, p2;

  QPainter painter(this);
  painter.setPen(g_color);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);

// Draw a gauge with centre at x0,y0
  painter.drawEllipse(centre.x()-r,centre.y()-r,r*2,r*2);

  rt=.95;
  for (i=0;i<=s_subtics*(s_tics-1);i++){
    l=(double)i/(double)(s_subtics*(s_tics-1));
    d=(endAng-startAng)*l+startAng;

    x=sin(d*PI/180.)*(double)r;
    y=-cos(d*PI/180.)*(double)r;
    p1=QPointF(x,y);
    p2=p1*rt;
    painter.drawLine(centre+p1,centre+p2);
  }

  rt=.90;
  for (i=0;i<s_tics;i++){
    l=(double)i/(double)(s_tics-1);
    d=(endAng-startAng)*l+startAng;

    x=sin(d*PI/180.)*(double)r;
    y=-cos(d*PI/180.)*(double)r;
    p1=QPointF(x,y);
    p2=p1*rt;
    painter.drawLine(centre+p1,centre+p2);
  }

  for (i=0;i<s_tics;i++){
    l=(double)i/(double)(s_tics-1);
    d=(endAng-startAng)*l+startAng;
    if (!s_int) sprintf(text,"%4.1f",l*(max-min)+min);
    if (s_int)  sprintf(text,"%i",(int)(l*(max-min)+min+.5));
    x=centre.x()+sin(d*PI/180.)*r*g_textRad;
    y=centre.y()-cos(d*PI/180.)*r*g_textRad;
    l=strlen(text)*7;
    h=14;
    if (endAng-360.!=startAng || i!=s_tics-1) painter.drawText((int)x-l/2,(int)y-h/2,l+2,h,Qt::AlignHCenter || Qt::AlignVCenter,text);
  }
  // We want the text forward of the dial background, but behind the arrow
  painter.drawText(centre.x()-50,centre.y()+r/4,100,20,Qt::AlignHCenter,name);
}


// Rectangular 100 series gauges
void gauge::draw_Plate100(){
  double ht, h=height()-20.;
  QPainter painter(this);
  painter.setPen(g_color);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);
  painter.drawRect(g_border,g_border,width()-g_border*2,h-g_border*2);
  ht=(g_value-min)/(max-min)*(double)(h-g_border*2);

  painter.setBrush(g_color);
  painter.drawRect(g_border,h-g_border,width()-g_border*2,-ht);
  painter.drawText(0,h,width(),20,Qt::AlignHCenter,name);
}


void gauge::draw_Plate101(){
  double wt, h=height()-20.;
  QPainter painter(this);
  painter.setPen(g_color);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);
  painter.drawRect(g_border,g_border,width()-g_border*2,h-g_border*2);
  wt=(g_value-min)/(max-min)*(double)(width()-g_border*2);

  painter.setBrush(g_color);
  painter.drawRect(g_border,g_border,wt, h-g_border*2);
  painter.drawText(0,h,width(),20,Qt::AlignHCenter,name);
}


void gauge::draw_Plate102(){
  double ht, h=height()-20., ht2;
  QPainter painter(this);

  painter.setPen(g_color);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);
  painter.drawRect(g_border,g_border,width()-g_border*2,h-g_border*2);
  ht=(g_value-min)/(max-min)*(double)(h-g_border*2);

  painter.drawLine(width()/2,h-g_border,width()/2,height()-ht-20);
  painter.drawLine(g_border,height()-ht-20,width()-g_border*2,height()-ht-20);
  painter.drawText(0,h,width(),20,Qt::AlignHCenter,name);
}


void gauge::draw_Plate103(){
}



void gauge::draw_Arrow0()
{
  double d;
  QPointF pt[5];
  QPainter painter(this);
  painter.setPen(g_color);
  painter.setRenderHint(QPainter::Antialiasing, g_antialias);

  d=(g_value-min)/(max-min)*(endAng-startAng)+startAng;

  pt[0]=QPointF(0,0);
  pt[1]=QPointF(0,-0.65*r+4.);
  pt[2]=QPointF(0,-0.65*r);
  pt[3]=QPointF(0,-0.65*r-4.);
  pt[4]=QPointF(0,-0.8*r);

  rotate(pt,5,d);
  translate(pt,5);
  painter.drawEllipse((int)pt[0].x()-2, (int)pt[0].y()-2, 4,4);
  painter.drawLine(pt[0],pt[1]);
  painter.drawEllipse((int)pt[2].x()-4, (int)pt[2].y()-4, 8,8);
  painter.drawLine(pt[3], pt[4]);
}


void gauge::setPlateType(int val){
  g_type=val;
  update();
  emit changed();
}

int gauge::plateType(){ return g_type; }

void gauge::setArrowType(int val){
  a_type=val;
  update();
  emit changed();
}

int gauge::arrowType(){ return a_type; }

void gauge::setAntialias(bool val){
  g_antialias=val;
  update();
  emit changed();
}

bool gauge::antialias(){ return g_antialias; }

void gauge::setValue(int val){ setValue((double)val); }

void gauge::setValue(double val){
  bool esafe=false, ewarn=false, edang=true;
  g_value=val;
  if (g_value<min) g_value=min;
  if (g_value>max) g_value=max;
  if (g_value>dmin && g_value<dmax) edang=true;
  if (g_value>wmin && g_value<wmax && !edang) ewarn=true;
  if (g_value>smin && g_value<smax && !edang && !ewarn) esafe=true;
  if (esafe) emit safe();
  if (ewarn) emit warn();
  if (edang) emit danger();
  update();
  emit changed();
}

double gauge::value(){ return g_value; }

int gauge::value_int(){ return (int)(g_value+.5); }

void gauge::setMaximum(double val){
  max=val;
  update();
  emit changed();
}

double gauge::maximum(){ return max; }

void gauge::setMinimum(double val){
  min=val;
  update();
  emit changed();
}

double gauge::minimum(){ return min; }

void gauge::setLabel(QString val){
  name=val;
  update();
  emit changed();
}

QString gauge::label(){ return name; }

void gauge::setSuffix(QString val){
  g_suffix=val;
  update();
  emit changed();
}

QString gauge::suffix(){ return g_suffix; }

void gauge::setTics(int val){
  s_tics=val;
  update();
  emit changed();
}

int gauge::tics(){ return s_tics; }

void gauge::setSubTics(int val){
  s_subtics=val;
  update();
  emit changed();
}

int gauge::subTics(){ return s_subtics; }

void gauge::setStartAngle(double val){
  startAng=val;
  update();
  emit changed();
}

double gauge::startAngle(){ return startAng; }

void gauge::setEndAngle(double val){
  endAng=val;
  update();
  emit changed();
}

double gauge::endAngle(){ return endAng; }

void gauge::setChevronWidth(double val){
  chev_width=val;
  update();
  emit changed();
}

double gauge::chevronWidth(){ return chev_width; }

void gauge::setQuality(int val){
  g_quality=val;
  update();
  emit changed();
}

int gauge::quality(){ return g_quality; }

void gauge::setBorder(int val){
  g_border=val;
  update();
  emit changed();
}

int gauge::border(){ return g_border; }

void gauge::setIntegerTics(bool val){
  s_int=val;
  update();
  emit changed();
}

bool gauge::integerTics(){ return s_int; }


void gauge::setTextRadius(double val){
  g_textRad=val;
  update();
  emit changed();
}

double gauge::textRadius(){ return g_textRad; }

void gauge::setGaugeColor(QColor val){
  g_color=val;
  update();
  emit changed();
}

QColor gauge::gaugeColor(){ return g_color; }

void gauge::setSafeMin(double val){
  smin=val;
  update();
  emit changed();
}

void gauge::setSafeMax(double val){
  smax=val;
  update();
  emit changed();
}

void gauge::setWarnMin(double val){
  wmin=val;
  update();
  emit changed();
}

void gauge::setWarnMax(double val){
  wmax=val;
  update();
  emit changed();
}

void gauge::setDangerMin(double val){
  dmin=val;
  update();
  emit changed();
}

void gauge::setDangerMax(double val){
  dmax=val;
  update();
  emit changed();
}

double gauge::safeMin(){ return smin; }
double gauge::safeMax(){ return smax; }
double gauge::warnMin(){ return wmin; }
double gauge::warnMax(){ return wmax; }
double gauge::dangerMin(){ return dmin; }
double gauge::dangerMax(){ return dmax; }


void gauge::setRangeWidth(double val){
  swdwidth=val;
  update();
  emit changed();
}

double gauge::rangeWidth(){ return swdwidth; }

void gauge::setShowRanges(bool val){
  g_showRanges=val;
  update();
  emit changed();
}

bool gauge::showRanges(){ return g_showRanges; }


void gauge::translate(QPointF pt[], int n){
  int i;
  for (i=0;i<n;i++) pt[i]=centre+pt[i];
}

void gauge::setDataScale(double s){
  datScale=s;
  update();
  emit changed();
}

double gauge::dataScale(){
  return datScale;
}

void gauge::rotate(QPointF pt[], int n, double theta){
  int i;
  double ix, iy;
  for (i=0;i<n;i++){
    ix=pt[i].x();
    iy=pt[i].y();
    pt[i].setX( ix*cos(-theta*PI/180.)+iy*sin(-theta*PI/180.) );
    pt[i].setY(-ix*sin(-theta*PI/180.)+iy*cos(-theta*PI/180.) );
  }
}
