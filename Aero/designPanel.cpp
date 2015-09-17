#include "designPanel.h"

designPanel::designPanel(guiDataStore *store, QList<guiPidLoop*> *pidLoops, QWidget *parent) : QWidget(parent){
  pid=pidLoops;
  cds=store;
  cds->setParent(this);

  contextMenu = new QMenu();
  addPID=contextMenu->addAction("Add PID Loop");
//  addInput=contextMenu->addAction("Add Input");
//  addOutput=contextMenu->addAction("Add Output");
  
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this,   SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
  connect(addPID, SIGNAL(activated()), this, SLOT(addPidLoopToPanel()));
}

void designPanel::showContextMenu(QPoint pos){
  QPoint gPos=mapToGlobal(pos);
  clickPosition=pos;
  contextMenu->exec(gPos);
}

void designPanel::addPidLoopToPanel(){
  printf("Adding PID Loop\n");
  
  pid->append(new guiPidLoop(this));
  pid->last()->setGeometry(clickPosition.x(),clickPosition.y(),150,60);
  pid->last()->show();
}