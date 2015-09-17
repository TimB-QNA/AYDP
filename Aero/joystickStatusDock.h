#ifndef joystickStatusDock_H
  #define joystickStatusDock_H

#include <QtGui>

class joystickStatusDock : public QDockWidget
{
   Q_OBJECT

  public:
    joystickStatusDock(QWidget *parent=0);
    
  public slots:
    void setDeviceInfo(QString name, int axes, int buttons);
    void setAxis(int c, double v);

  private:
    QLabel *label;
    QList<QProgressBar*> barList;
    QBoxLayout *axisLayout;
};

#endif

