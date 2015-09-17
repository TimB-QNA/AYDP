#include <QApplication>
#include <QtXml>
#include "mainWindow.h"

int main(int argc, char * argv[]){
  int i;
  QApplication app(argc,argv);

  mainWindow *evLoop=new mainWindow();
  
  evLoop->show();
  
  return app.exec();
}
