#include "guiPidLoop.h"

guiPidLoop::guiPidLoop(QWidget *parent) : pidControl(parent){
  initialSetup();
  QGridLayout *gridLayout = new QGridLayout();
  frontLabel = new QLabel(); gridLayout->addWidget(frontLabel,0,0);
//  updateFrontLabel();
  connect(this, SIGNAL(control(int, float)), this, SLOT(updateFrontLabel()));
  setLayout(gridLayout);
  setup();
/*  
  pLabel = new QLabel(); pLabel->setText("Proportional"); gridLayout->addWidget(pLabel,0,0);
  iLabel = new QLabel(); iLabel->setText("Integral"); gridLayout->addWidget(iLabel,1,0);
  ilLabel = new QLabel(); ilLabel->setText("Int Limit"); gridLayout->addWidget(ilLabel,2,0);
  dLabel = new QLabel(); dLabel->setText("Derivative"); gridLayout->addWidget(dLabel,3,0);
  tLabel = new QLabel(); tLabel->setText("Target"); gridLayout->addWidget(tLabel,4,0);
  cLabel = new QLabel(); cLabel->setText("Control"); gridLayout->addWidget(cLabel,6,0);
  cvLabel = new QLabel(); cvLabel->setText("0.000"); gridLayout->addWidget(cvLabel,6,1);
    
  pSpin = new QDoubleSpinBox(); pSpin->setMinimum(-100); pSpin->setMaximum(100); pSpin->setValue(-1); gridLayout->addWidget(pSpin,0,1);
  iSpin = new QDoubleSpinBox(); iSpin->setMinimum(-100); iSpin->setMaximum(100); iSpin->setValue(0);  gridLayout->addWidget(iSpin,1,1);
  ilSpin = new QDoubleSpinBox(); ilSpin->setMinimum(0);  ilSpin->setMaximum(100); ilSpin->setValue(1);  gridLayout->addWidget(ilSpin,2,1);
  dSpin = new QDoubleSpinBox(); dSpin->setMinimum(-100); dSpin->setMaximum(100); dSpin->setValue(0);  gridLayout->addWidget(dSpin,3,1);
  tSpin = new QDoubleSpinBox(); tSpin->setMinimum(-1e6); tSpin->setMaximum(1e6); tSpin->setValue(20); gridLayout->addWidget(tSpin,4,1);
  active= new QCheckBox("Active"); active->setChecked(false); gridLayout->addWidget(active,5,1);
*/  

}

void guiPidLoop::showEvent(QShowEvent *event){
//  pSpin->setValue(kP);
//  iSpin->setValue(kI);
//  dSpin->setValue(kD);
//  tSpin->setValue(target);
//  active->setChecked(active);
  
//  connect(pSpin,  SIGNAL(valueChanged(double)), this, SLOT(setPGain(double)));
//  connect(iSpin,  SIGNAL(valueChanged(double)), this, SLOT(setIGain(double)));
//  connect(dSpin,  SIGNAL(valueChanged(double)), this, SLOT(setDGain(double)));
//  connect(active, SIGNAL(clicked(bool)),        this, SLOT(setActive(bool)));
}

void guiPidLoop::paintEvent(QPaintEvent *event){
  QColor colour;
  QPainter painter(this);
  if (active)  colour=QColor(0,125,0);
  if (!active) colour=QColor(125,0,0);
  
  painter.fillRect(0, 0, width(), height(), colour);
}

void guiPidLoop::updateFrontLabel(){
  char line[40];
  QString text;
  text ="<html>";
  text+=  "<table>";
  sprintf(line,"<tr><th>Signal</th><td>%0.3f</td></tr>",*signal); text+=line;
  sprintf(line,"<tr><th>Target</th><td>%0.3f</td></tr>",target); text+=line;
  sprintf(line,"<tr><th>Control</th><td>%0.3f</td></tr>",controlValue); text+=line;
  text+=  "</table>";
  text+=  "</html>";
  frontLabel->setText(text);
}