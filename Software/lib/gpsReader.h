/*
    Description: Provide GPS Position and lock data input for AYDP
         Author: Tim Brocklehurst
        Version: 1.0-0
           Date: 23 February 2016
        License: GPLv3
*/

#ifndef GPSREADER_H
  #define GPSREADER_H

#include <termios.h>
#include <sys/time.h>
#include <vector>
#include "dataCollector.h"
#include "dataStore.h"

using namespace std;

class gpsReader : public dataCollector
{
   Q_OBJECT

  public:
    gpsReader(QThread *parent, dataStore *vData);   
    void readSettings(QDomNode root);

    void run();

  private slots:
    void getData(int);
    void close();
    int  extractSentence();
    
  private:
    int fd, baud, bufferSizeLimit;
    QString device;
    QByteArray buffer;
    QSocketNotifier *notifier;
    
    unsigned int checksum(QByteArray sentence);
};

#endif
