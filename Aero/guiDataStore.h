#ifndef guiDataStore_H
  #define guiDataStore_H

  #include <QtGui>
  #include "../Vessel/src/dataStore.h"

class guiDataStore : public QWidget
{
   Q_OBJECT

  public:
    guiDataStore(dataStore *ds, QWidget *parent=0);

  private:
    dataStore *cds;
    QLabel *frontLabel;
    QTimer *updateTimer;
    void paintEvent(QPaintEvent *event);
    
  private slots:
    void updateFrontLabel();
};

#endif

