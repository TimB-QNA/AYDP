#include "pidLoopWidget.h"

pidLoopWidget::pidLoopWidget(QWidget *parent) : QWidget(parent){
  QGridLayout *gridLayout = new QGridLayout();
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
  
  setLayout(gridLayout);
}

void pidLoopWidget::setPIDLoop(pidControl *pid){
  pidLoop=pid;
  
  pSpin->setValue(pidLoop->kP);
  iSpin->setValue(pidLoop->kI);
  dSpin->setValue(pidLoop->kD);
  tSpin->setValue(pidLoop->target);
  active->setChecked(pidLoop->isActive());
  
  connect(pSpin,  SIGNAL(valueChanged(double)), pidLoop, SLOT(setPGain(double)));
  connect(iSpin,  SIGNAL(valueChanged(double)), pidLoop, SLOT(setIGain(double)));
  connect(dSpin,  SIGNAL(valueChanged(double)), pidLoop, SLOT(setDGain(double)));
  connect(active, SIGNAL(clicked(bool)),        pidLoop, SLOT(setActive(bool)));
  connect(pidLoop, SIGNAL(control(int, float)), this,    SLOT(control(int, float)));
}

void pidLoopWidget::control(int chan, float value){
  char line[128];
  sprintf(line, "%0.3f", value);
  cvLabel->setText(line);
}