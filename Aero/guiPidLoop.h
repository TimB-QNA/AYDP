#ifndef guiPidLoop_H
  #define guiPidLoop_H

  #include <QtGui>
  #include "../Vessel/src/pidControl.h"

class guiPidLoop : public pidControl
{
   Q_OBJECT

  public:
    guiPidLoop(QWidget *parent=0);

  private:
    QLabel *frontLabel;
     
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

    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);
    
  private slots:
    void updateFrontLabel();
};

#endif

