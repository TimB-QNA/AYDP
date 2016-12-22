// Autonomous yacht development platform main program

#include <QApplication>
#include "mainWindow.h"

void header();

int main(int argc, char * argv[]){
  QApplication app(argc,argv);
  header();

  mainWindow *mainWin = new mainWindow();
  
  mainWin->show();
  
  return app.exec();
}

void header(){
  printf("AYDP Base Station\n");
  printf("\n");
  printf("  Version: %s\n", VERSION.toAscii().data());
  printf("   Author: Tim Brocklehurst - timb@engineering.selfip.org\n");
  printf("\n");
}