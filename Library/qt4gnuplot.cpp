/*
    Description: Provide Gnuplot graphs for QT4
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/


#include <QtGui>
#include "qt4gnuplot.h"

qt4gnuplot::qt4gnuplot(QWidget *parent)
                     : QWidget(parent)
{
  printf("Initialising OpenPilot::qt4gnuplot\n");
  bk=false;
  bg=QColor(0,0,0);
  forceXRange=false;
  forceYRange=false;
  script.append("set grid");
  script.append("plot x**3+4*x**2+0");
  connect(&gnuplot, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(plotComplete(int, QProcess::ExitStatus)) );
  plotgraph();
}

void qt4gnuplot::paintEvent(QPaintEvent *event){
  QPointF target(0.0, 0.0);
  QPainter painter(this);
  if (bk){
    painter.drawRect(0,0,width()-1,height()-1);
  }
  painter.drawImage(target, image);
}

void qt4gnuplot::resizeEvent(QResizeEvent *event){
  plotgraph();
}

void qt4gnuplot::plotgraph(QStringList data){
  script=data;
  plotgraph();
}

void qt4gnuplot::plotgraph(){
  int i, length;
  char cmd[4096];
  QString tmp;
  if (gnuplot.state()==QProcess::Running) return;
  sprintf(cmd,"set title \"%s\"\n",titl.toAscii().data()); script.prepend(cmd);
  sprintf(cmd,"set xlabel \"%s\"\n",xlab.toAscii().data()); script.prepend(cmd);
  sprintf(cmd,"set ylabel \"%s\"\n",ylab.toAscii().data()); script.prepend(cmd);
  sprintf(cmd,"set zlabel \"%s\"\n",zlab.toAscii().data()); script.prepend(cmd);
  if (hasGrid()) sprintf(cmd,"set grid\n"); script.prepend(cmd);

  gnuplot.start("gnuplot");
  gnuplot.waitForStarted();
  sprintf(cmd,"set terminal gif size %i,%i transparent\n",width(),height()); gnuplot.write(cmd);
  if (forceXRange){ sprintf(cmd,"set xrange [%lf:%lf]\n",xMin,xMax); gnuplot.write(cmd); }
  if (forceYRange){ sprintf(cmd,"set yrange [%lf:%lf]\n",yMin,yMax); gnuplot.write(cmd); }
  for (i=0;i<script.size();i++) gnuplot.write((script.at(i)+"\n").toLocal8Bit().constData());
  gnuplot.write("quit\n");
}

void qt4gnuplot::plotComplete(int exitCode, QProcess::ExitStatus exitStatus){
  if (exitCode==0){
    QByteArray result = gnuplot.readAllStandardOutput();
    image.loadFromData(result);
  }
  update();
}

QImage qt4gnuplot::graph(QStringList data, QRect geom){
  QImage store;
  int i, length;
  char cmd[4096];
  QString tmp;
  script=data;

  sprintf(cmd,"set title \"%s\"\n",titl.toAscii().data()); script.prepend(cmd);
  sprintf(cmd,"set xlabel \"%s\"\n",xlab.toAscii().data()); script.prepend(cmd);
  sprintf(cmd,"set ylabel \"%s\"\n",ylab.toAscii().data()); script.prepend(cmd);
  sprintf(cmd,"set zlabel \"%s\"\n",zlab.toAscii().data()); script.prepend(cmd);

  gnuplot.start("gnuplot");
  gnuplot.waitForStarted();
  sprintf(cmd,"set terminal gif size %i,%i transparent\n",geom.width(),geom.height());
  gnuplot.write(cmd);
  for (i=0;i<script.size();i++) gnuplot.write((script.at(i)+"\n").toLocal8Bit().constData());
  gnuplot.write("quit\n");
  gnuplot.waitForFinished();
  if (gnuplot.exitCode()==0){
    QByteArray result = gnuplot.readAllStandardOutput();
    store.loadFromData(result);
  }
  return store;
}


void qt4gnuplot::setTitle(QString data){
  titl=data;
  plotgraph();
}

QString qt4gnuplot::title(){
  return titl;
}

void qt4gnuplot::setXLabel(QString data){
  xlab=data;
  plotgraph();
}

QString qt4gnuplot::xLabel(){
  return xlab;
}

void qt4gnuplot::setYLabel(QString data){
  ylab=data;
  plotgraph();
}

QString qt4gnuplot::yLabel(){
  return ylab;
}

void qt4gnuplot::setZLabel(QString data){
  zlab=data;
  plotgraph();
}

QString qt4gnuplot::zLabel(){
  return zlab;
}

void qt4gnuplot::setGrid(bool yesno){
  grid=yesno;
  plotgraph();
}

bool qt4gnuplot::hasGrid(){
  return grid;
}
