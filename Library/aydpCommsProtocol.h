#ifndef AYDPCOMMSPROTOCOL_H
#define AYDPCOMMSPROTOCOL_H
#ifndef x86
  #define arduino
#endif

#include "typedef.h"

#ifndef arduino
  #include <QVector>
  #include <QString>
#endif


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
    struct timeval tv;
} __attribute__((packed)) aydpCommsProtoHeader;

class registeredBoolean {
  public:
    QString name;
    bool *data;
};

class registeredInteger {
  public:
    QString name;
    int *data;
};

class registeredFloat {
  public:
    QString name;
    float *data;
};

class aydpCommsProtocol {
  public:
    int messLength;
    aydpCommsProtoHeader header;
    unsigned char *message;
    QVector<registeredBoolean> regBool;
    QVector<registeredInteger>  regInt;
    QVector<registeredFloat>   regFloat;
    
    aydpCommsProtocol();
    void useSocket(QTcpSocket skt);
    
    void registerBoolean(QString name, bool *source, bool isRemote=false, int id=-1);
    void registerInteger(QString name, int *source, bool isRemote=false, int id=-1);
    void registerFloat(QString name, float *source, bool isRemote=false, int id=-1);
    void listRegisteredVariables();
    
    void createFloatMessage(struct timeval sysTime, int type, int nData, float *inData);
//    int  parseWindMessage(unsigned char *msg, unsigned int nbytes, aydpTime *sysTime, float *windSpeed, float *windDirection);
    
  private:
    void createChecksum();
    void checkEndianness();
    bool isLittleEndian;
    QTCPSocket *interface;
};

#endif
