#include "dataCollector.h"
#include <stdio.h>

dataCollector::dataCollector(QThread *parent, dataStore *vData) : QThread(parent)
{
  vesselData=vData;
}

void dataCollector::readSettings(QDomNode root){
}