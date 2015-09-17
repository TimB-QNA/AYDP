#ifndef designPanel_H
  #define designPanel_H

  #include <QtGui>
  #include "guiPidLoop.h"
  #include "guiDataStore.h"
  
class designPanel : public QWidget
{
   Q_OBJECT

  public:
    designPanel(guiDataStore *store, QList<guiPidLoop*> *pidLoops, QWidget *parent=0);
    
  public slots:

  private:
    QPoint clickPosition;
    QMenu *contextMenu;
    QAction *addPID, *addInput, *addOutput;
    
    QList<guiPidLoop*> *pid;
    guiDataStore *cds;
    
  private slots:
    void showContextMenu(QPoint pos);
    void addPidLoopToPanel();
};

#endif

