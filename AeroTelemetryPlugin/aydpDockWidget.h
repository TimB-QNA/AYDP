#ifndef aydpDockWidget_H
  #define aydpDockWidget_H

#include <QtGui>
#include "../Vessel/src/dataStore.h"

class aydpDockWidget : public QWidget
{
  public:
    aydpDockWidget(QWidget *parent=0, dataStore *vData=0);
    
  private:
    dataStore *vessel;
};

#endif

