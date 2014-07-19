#ifndef AYDPCOMMSPROTOCOL_H
#define AYDPCOMMSPROTOCOL_H

#ifndef x86
  #define arduino
#endif

#include "aydpTime.h"

typedef struct{
    unsigned char start;
    unsigned char type;
#ifdef arduino
    unsigned long int length;
#endif
#ifdef x86
    unsigned int length;
#endif
    // Time Info in header
#ifdef arduino
    long int year;
    unsigned long int day;
#endif
#ifdef x86
    int year;
    unsigned int day;
#endif
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
#ifdef arduino
    unsigned long int micro;
#endif
#ifdef x86
    unsigned int micro;
#endif
} __attribute__((packed)) aydpCommsProtoHeader;

class aydpCommsProtocol {
  public:
    aydpCommsProtoHeader header;
    unsigned char *data;
    unsigned char checksum;
    
    aydpCommsProtocol();
    void createWindMessage(aydpTime sysTime, float windSpeed, float windDirection);
    int  parseWindMessage(unsigned char *msg, unsigned int nbytes, aydpTime *sysTime, float *windSpeed, float *windDirection);
    
  private:  
    void setupHeaderFooter(aydpTime sysTime);
    
    
};

#endif
