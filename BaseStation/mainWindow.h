#ifndef mainWindow_H
  #define mainWindow_H

#include <QMainWindow>
#include "windData.h"

/*! Main Window for base-station software
 *
 */
class mainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    mainWindow(QMainWindow *parent=0);
    
  private:
    windData *wind;
    
  private slots:
};

#endif
