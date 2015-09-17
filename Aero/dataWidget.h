#ifndef pidLoopWidget_H
  #define pidLoopWidget_H

  #include <QtGui>
  #include "../Vessel/src/pidControl.h"

class pidLoopWidget : public QWidget
{
   Q_OBJECT

  public:
    pidLoopWidget(QWidget *parent=0);
    void setPIDLoop(pidControl *pid);
    
  public slots:
    void control(int chan, float value);

  private:
    QLabel *pLabel;
    QLabel *iLabel;
    QLabel *dLabel;
    
    QDoubleSpinBox *pSpin;
    QDoubleSpinBox *iSpin;
    QDoubleSpinBox *dSpin;
    
    QLabel *tLabel;
    QDoubleSpinBox *tSpin;
    
    QCheckBox *active;

    QLabel *cLabel;
    QLabel *cvLabel;

    QLabel *ilLabel;
    QDoubleSpinBox *ilSpin;
    
    pidControl *pidLoop;
};

#endif

