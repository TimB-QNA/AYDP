#include "eventLoop.h"
#include "../gpsReader.h"
#include <stdio.h>

eventLoop::eventLoop(QObject *parent) : QObject(parent)
{
  int i;

  log = new logOutput();

  log->setFileName("AYDP_LogFile.csv");
  vesselData.setupLogOutput(log);
        
  input.append(new gpsReader(0, &vesselData));
  
  readSettings("settings.xml");
  
  printf("Starting log system\n");
  log->start();
  
  // Start input threads
  for (i=0;i<input.count();i++){
    printf("Starting %s\n",input[i]->objectName().toLatin1().data());
    input[i]->start();
  }
}

void eventLoop::readSettings(QString fileName){
  // Read settings file...
  int i;
  int erl, erc;
  QDomNode node, node2;
  QDomElement root, element, element2;
  QString errMsg;
  QFile file;
  
  file.setFileName(fileName);
  if (!file.open( QIODevice::ReadOnly )){
    printf("Could not open XML settings file - %s\n",fileName.toLatin1().data());
    return;
  }

  QDomDocument doc( "sessionFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("Error at line %i, Column %i - %s\n", erl, erc,errMsg.toLatin1().data());
    file.close();
    return;
  }
  file.close();

  root=doc.documentElement();
  if (root.tagName().toLower() != "aydp"){
    printf("This is not an AYDP configuration file\n");
    return;
  }

  node=root.firstChild();
  while (!node.isNull()){
    for (i=0;i<input.count();i++) input[i]->readSettings(node);
    node=node.nextSibling();
  }
}
