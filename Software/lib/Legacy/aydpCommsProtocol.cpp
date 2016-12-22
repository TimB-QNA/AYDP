#include "aydpCommsProtocol.h"
#include <stdio.h>
#include <string.h>

aydpCommsProtocol::aydpCommsProtocol(){
  messLength=0;
  checkEndianness();
}

void aydpCommsProtocol::useSocket(QTcpSocket *skt){
  interface=skt;  
}

void aydpCommsProtocol::checkEndianness(){
  unsigned int ce=1;
  unsigned char et;
  memcpy(&et, &ce, 1); // copy the first byte to et.
  isLittleEndian=true;
  if (et==0) isLittleEndian=false;
}

void aydpCommsProtocol::registerBoolean(QString name, bool *source, bool isRemote, int id){
  int i;
  // If id<0 then append to the end of the array...
  if (id<0){
    id=regBool.size();
  }
  
  if (id>regBool.size()-1){
    regBool.resize(id+1);
    // Having resized, set any null pointers to real objects
    // This is horribly unclean, but not creating objects would be worse...
    for (i=0;i<regBool.size()-1;i++){
      if (regBool[id].data==NULL) regBool[id].data = new bool;
    }
  }

  regBool[id].name=name;
  if (isRemote)  regBool[id].data = new bool;
  if (!isRemote) regBool[id].data=source;
  
  
//  if (!isRemote) sendRegisterBoolMessage(id, regBool[id]);
}

void aydpCommsProtocol::registerInteger(QString name, int *source, bool isRemote, int id){
  int i;
  // If id<0 then append to the end of the array...
  if (id<0){
    id=regInt.size();
  }
  
  if (id>regInt.size()-1){
    regInt.resize(id+1);
    // Having resized, set any null pointers to real objects
    // This is horribly unclean, but not creating objects would be worse...
    for (i=0;i<regInt.size()-1;i++){
      if (regInt[id].data==NULL) regInt[id].data = new int;
    }
  }

  regInt[id].name=name;
  if (isRemote)  regInt[id].data = new int;
  if (!isRemote) regInt[id].data=source;
  
//  if (!isRemote) sendRegisterIntegerMessage(id, regFloat[id]);  
}

void aydpCommsProtocol::registerFloat(QString name, float *source, bool isRemote, int id){
  int i;
  // If id<0 then append to the end of the array...
  if (id<0){
    id=regFloat.size();
  }
  
  if (id>regFloat.size()-1){
    regFloat.resize(id+1);
    // Having resized, set any null pointers to real objects
    // This is horribly unclean, but not creating objects would be worse...
    for (i=0;i<regFloat.size()-1;i++){
      if (regFloat[id].data==NULL) regFloat[id].data = new float;
    }
  }

  regFloat[id].name=name;
  if (isRemote)  regFloat[id].data = new float;
  if (!isRemote) regFloat[id].data=source;
  
//  if (!isRemote) sendRegisterFloatMessage(id, regFloat[id]);  
}
    
void aydpCommsProtocol::listRegisteredVariables(){
  int i;
  printf("Registered boolean variables:\n");
  for (i=0;i<regBool.size();i++){
    printf("  Index: %i\n", i);
    printf("   Name: %s\n", regBool[i].name.toAscii().data());
    printf("  Value: ");
    if (*regBool[i].data) printf("T\n");
    if (!*regBool[i].data) printf("F\n");
    printf("\n");
  }
  
  printf("Registered integer variables:\n");
  for (i=0;i<regInt.size();i++){
    printf("  Index: %i\n", i);
    printf("   Name: %s\n", regInt[i].name.toAscii().data());
    printf("  Value: %i\n", *regInt[i].data);
    printf("\n");
  }
  
  printf("Registered floating point variables:\n");
  for (i=0;i<regFloat.size();i++){
    printf("  Index: %i\n", i);
    printf("   Name: %s\n", regFloat[i].name.toAscii().data());
    printf("  Value: %f\n", *regFloat[i].data);
    printf("\n");
  }
}
  
void aydpCommsProtocol::createFloatMessage(struct timeval sysTime, int type, int nData, float *inData){
  int i, size=sizeof(float);
//  aydpCommsProtoHeader header;
  
  header.start=0xFF;  
  header.type=type;
  header.length=nData*size;
  header.tv=sysTime;

  if (messLength!=0) delete message;
  messLength=sizeof(header)+header.length+1;
  message = new unsigned char [messLength];  
  memcpy(message, &header, sizeof(header));
 
  for (i=0;i<nData;i++) memcpy(&message[sizeof(header)+i], &inData[i*size], size);
  
  createChecksum();
}

void aydpCommsProtocol::createChecksum(){
  int i;
  unsigned char checksum;
  checksum=message[0];
  for (i=1;i<messLength-1;i++) checksum^=message[i];
  message[messLength-1]=checksum;
}

QByteArray aydpCommsProtocol::createDataStoreMsg(dataStore *ds){
  struct timeval sysTime;
  
  gettimeofday(&sysTime, NULL);
  
  header.start=0xFF;  
  header.type=17;
  header.length=sizeof(*ds);
  header.tv=sysTime;

  if (messLength!=0) delete message;
  messLength=sizeof(header)+header.length+1;
  message = new unsigned char [messLength];  
  memcpy(message, &header, sizeof(header));
  memcpy(&message[sizeof(header)], ds, sizeof(*ds));
  createChecksum();
  
  return QByteArray((char*)message, messLength);
}

/*!
 * Return states have the following meanings:
 * +ve - Message read sucessfully (Number of bytes)
 * -1 - Message too short
 * -2 - Start byte incorrect
 * -3 - Type incorrect 
 */
/*
int aydpCommsProtocol::parseWindMessage(unsigned char *msg, unsigned int nbytes, aydpTime *sysTime, float *windSpeed, float *windDirection){ 
  int i;
  if (nbytes<sizeof(header)) return -1;
  if (msg[0]!=0xff) return -2;
  if (msg[1]!=0x01) return -3;
  
  memcpy(&header,msg,sizeof(header));
  
//  printf("Total header size should be %i\n",sizeof(header)+header.length+1);
  if (nbytes<sizeof(header)+header.length+1) return -1;
  
  delete data;
  data = new unsigned char[header.length];
  memcpy(data,msg+sizeof(header),header.length);
  
  checksum=msg[sizeof(header)+header.length];
  
  printf("Start    = 0x%02x\n",header.start);
  printf("Type     = %i\n",header.type);
  printf("Length   = %i\n",header.length);
  printf("Year     = %i\n",header.year);
  printf("Day      = %i\n",header.day);
  printf("Hour     = %i\n",header.hour);
  printf("Min      = %i\n",header.min);
  printf("Sec      = %i\n",header.sec);
  printf("Micro    = %i\n",header.micro);
  printf("Data     = ");
  for (i=0;i<header.length;i++){
    printf("0x%02x ",data[i]);
  }
  printf("\n");
  printf("Checksum = 0x%02x\n",checksum);
  
  // Extract time data...
  sysTime->year = header.year;
  sysTime->day  = header.day;
  sysTime->hour = header.hour;
  sysTime->min  = header.min;
  sysTime->sec   = header.sec;
  sysTime->micro = header.micro;
  
  // return wind speed and direction by doing some more memory copies...
  memcpy(windSpeed, data, 4);
  memcpy(windDirection, data+4, 4);
  
  return sizeof(header)+header.length+1;
}
*/
