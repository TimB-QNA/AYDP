#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "/usr/include/linux/i2c-dev.h"

// Note requires libi2c-dev to be installed
union conv
{
  char b[2];
  short int i;
};

float dotProduct(float ax, float ay, float bx, float by);

int main(){
  char device[]="/dev/i2c-1";
  int file;
  int i;
  
  file = open(device, O_RDWR);
  if (file < 0) {
    printf("Failed to open device /dev/i2c-1\n");
    return 1;
  }

// When you have opened the device, you must specify with what device
// address you want to communicate:

  if (ioctl(file, I2C_SLAVE, 0x1e) < 0) {
    printf("Failed to open device 0x1e\n");
  }
  
  printf("Returned byte 0x%02x\n",i2c_smbus_read_byte_data(file, 10));
  printf("Returned byte 0x%02x\n",i2c_smbus_read_byte_data(file, 11));
  printf("Returned byte 0x%02x\n",i2c_smbus_read_byte_data(file, 12));
  
  // Set gain
  i2c_smbus_write_byte_data(file, 0x01, (0)<<5);
  
  // Take single measurement
  unsigned char rb[24];
  conv bc;
  float x, y, z;    // Raw data
  float xAng, yAng, zAng;    // Angle output
  float x0, y0, z0; // Correction offsets
  float xc, yc, zc; // Corrected
  float xd, yd, zd; // Datum (after correction)
  x0=0.101095;
  y0=-0.0751825;
  z0=0.1456205;
  
  xd=-0.441566766+x0;
  yd=-0.4295720588+y0;
  zd=0.0975763921+z0;
  
  xd=0; yd=0; zd=0;
  for (i=0;i<100;i++){
    i2c_smbus_write_byte_data(file, 2, 0x01);
    i2c_smbus_write_byte(file, 3);
    usleep(6250);
    read(file, rb, 6);
    bc.b[0]=rb[1]; bc.b[1]=rb[0]; xd+=((float)bc.i)/1370.+x0;
    bc.b[0]=rb[3]; bc.b[1]=rb[2]; yd+=((float)bc.i)/1370.+y0;
    bc.b[0]=rb[5]; bc.b[1]=rb[4]; zd+=((float)bc.i)/1370.+z0;
    usleep(20*1000); // sleep 20ms
  }
  xd/=100.; yd/=100.; zd/=100.;
  printf("Datum %lf %lf %lf\n",xd,yd,zd);
  
  while(true){
    // Set Mode
    i2c_smbus_write_byte_data(file, 2, 0x01);
    // Start measurement
    i2c_smbus_write_byte(file, 3);
    // allow to complete
    usleep(6250);
    // read data
    read(file, rb, 6);
 //   for (i=0;i<6;i++) printf("0x%02x  ",rb[i]);
 //   printf("\n");
    bc.b[0]=rb[1]; bc.b[1]=rb[0]; xc=((float)bc.i)/1370.+x0;
    bc.b[0]=rb[3]; bc.b[1]=rb[2]; yc=((float)bc.i)/1370.+y0;
    bc.b[0]=rb[5]; bc.b[1]=rb[4]; zc=((float)bc.i)/1370.+z0;

  //  printf("Corrected %lf %lf %lf\n",xc,yc,zc);
    
    xAng=dotProduct(yc, zc, yd, zd);
    yAng=dotProduct(xc, zc, xd, zd);
    zAng=dotProduct(xc, yc, xd, yd);
    
    printf("Angles    %lf %lf %lf  -- ATAN2(y,x) %lf\n",xAng,yAng,zAng, atan2(yc,xc)*180./3.14159);
    usleep(100*1000); // sleep 100ms
 //   sleep(1);
  }  
  printf("Size of short int = %i\n",sizeof(short int));
/*
  unsigned char wb[12];
  
  // Setup
  wb[0]=0x3C;
  wb[1]=0x00;
  wb[2]=0x71;
  write(file, wb, 3);
  
  wb[0]=0x3C;
  wb[1]=0x01;
  wb[2]=0xA0;
  write(file, wb, 3);
  
  wb[0]=0x3C;
  wb[1]=0x02;
  wb[2]=0x00;
  write(file, wb, 3);
  
  unsigned char rb[24];
  while(true){
    sleep(1);
    // Read data
    wb[0]=0x3D;
    wb[1]=0x06;
    write(file, wb, 2);
  
    read(file, rb, 6);
    for (i=0;i<6;i++) printf("0x%02x ",rb[i]);
    printf("\n");
  
    // Read data
    wb[0]=0x3D;
    wb[1]=0x06;
    write(file, wb, 2);
  }
  */
  close(file);
}

float dotProduct(float ax, float ay, float bx, float by){
  float pi=4.*atan(1);
  float ctht=(ax*bx + ay*by)/(sqrt(ax*ax+ay*ay)*sqrt(bx*bx+by*by));
  return acos(ctht)*180./pi;
}