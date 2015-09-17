#include "joystickStatusDock.h"

joystickStatusDock::joystickStatusDock(QWidget *parent) : QDockWidget("Joystick",parent){
  
  QWidget *bckWidget = new QWidget(this);
  QBoxLayout *dockLayout = new QBoxLayout(QBoxLayout::TopToBottom, bckWidget);
  label = new QLabel(this);  dockLayout->addWidget(label);
  QWidget *drawn = new QWidget(this); dockLayout->addWidget(drawn);
  axisLayout = new QBoxLayout(QBoxLayout::TopToBottom, drawn);
  setWidget(bckWidget);
  label->setText("Name:\nAxes:\nChannels:");
}

void joystickStatusDock::setAxis(int c, double v){
  int i;
  printf("Setting Value\n");
  barList[c]->setValue(v);
}

void joystickStatusDock::setDeviceInfo(QString name, int axes, int buttons){
  int i;
  printf("%s   -   %i    -    %i\n",name.toAscii().data(), axes, buttons);
  label->setText(QString("Name: ")+name+QString("\nAxes: %1\nChannels: %2").arg(axes).arg(buttons));

  for (i=0;i<barList.size();i++) delete barList[i];
  barList.clear();  
  
  setWindowTitle(name);
  
  for (i=0;i<axes;i++){
    barList.append(new QProgressBar(this));
    axisLayout->addWidget(barList.last());
    barList.last()->setMinimum(0);
    barList.last()->setMaximum(100);
  }
}