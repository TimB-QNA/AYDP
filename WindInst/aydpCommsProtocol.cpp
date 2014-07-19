#include "aydpCommsProtocol.h"
#include <stdio.h>
#include <string.h>

aydpCommsProtocol::aydpCommsProtocol(){
  data = new unsigned char[1];
}

void aydpCommsProtocol::createWindMessage(aydpTime sysTime, float windSpeed, float windDirection){
  header.type=1;
  header.length=2*sizeof(float);
  delete data;
  data = new unsigned char[header.length];
  memcpy(&data[0],&windSpeed, 4);
  memcpy(&data[4],&windDirection, 4);
  setupHeaderFooter(sysTime);
}

void aydpCommsProtocol::setupHeaderFooter(aydpTime sysTime){
  header.start=0xFF;
  header.year =sysTime.year;
  header.day  =sysTime.day;
  header.hour =sysTime.hour;
  header.min  =sysTime.min;
  header.sec  =sysTime.sec;
  header.micro=sysTime.micro;
  
  checksum=0x00;
}


/*!
 * Return states have the following meanings:
 * +ve - Message read sucessfully (Number of bytes)
 * -1 - Message too short
 * -2 - Start byte incorrect
 * -3 - Type incorrect 
 */
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
/*  
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
*/  
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
