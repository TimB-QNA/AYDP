#include <QCoreApplication>
#include <QtXml>
#include "eventLoop.h"

int main(int argc, char * argv[]){
  int i;
  QCoreApplication app(argc,argv);

  eventLoop *evLoop=new eventLoop();
  
  return app.exec();
}
