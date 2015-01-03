#include "maestro.h"
#include <stdio.h>
#include <stdlib.h>

maestro::maestro(QObject *parent) : QObject(parent){
  channel.clear(); channel.resize(24); // initialise channels to maximum number.
  printf("OpenPilot::Servo - Initialising\n");
  if (libusb_init(&ctx)<0){
    printf("OpenPilot::Servo - Failed to initialise USB. Cannot Continue\n");
    return;
  }

//    Level 0: no messages ever printed by the library (default)
//    Level 1: error messages are printed to stderr
//    Level 2: warning and error messages are printed to stderr
//    Level 3: informational messages are printed to stdout, warning and error messages are printed to stderr
  libusb_set_debug(ctx, 3);
}

void maestro::orderPosition(int srv, float position){
  int value=4.*channel[srv].calibrated(position)+.5;
  unsigned char string[256];
//  printf("OpenPilot::maestro - Handling %i, %lf\n", srv, position);

  if (srv<0 || srv>nChans-1) return;
  if (value<4000 && value!=0) value=4000;
  if (value>8000) value=8000;

  libusb_control_transfer(devHandle, 0x40, 0x85, value, srv, string, sizeof(string),0);
  // libusb_close(devHandle);
  // libusb_exit(ctx);
}

void maestro::listDevices(){
  int i, nDev, r, busNo, devNo;
  unsigned char string[256];
  libusb_device_descriptor desc;
  libusb_device_handle *listHandle;

  nDev = libusb_get_device_list(ctx, &devList);
  if (nDev==0){
    printf("OpenPilot::Servo - Failed to get device list. Cannot Continue\n");
    return;
  }

  for (i=0;i<nDev;i++){
    r=libusb_get_device_descriptor(devList[i], &desc);
    if (r!=0) continue;

    busNo=libusb_get_bus_number(devList[i]);
    devNo=libusb_get_device_address(devList[i]);
    printf("OpenPilot::Servo - Device: %03i/%03i\n",busNo,devNo);
    printf("OpenPilot::Servo -    Class: 0x%02X\n",(int)desc.bDeviceClass);

    if (libusb_open(devList[i],&listHandle)==0){
      libusb_get_string_descriptor_ascii(listHandle,desc.iManufacturer,string,sizeof(string));
      printf("OpenPilot::Servo -   Vendor: 0x%04X - %s\n",desc.idVendor, string);
      libusb_get_string_descriptor_ascii(listHandle,desc.iProduct,string,sizeof(string));
      printf("OpenPilot::Servo -  Product: 0x%04X - %s\n",desc.idProduct, string);
      libusb_get_string_descriptor_ascii(listHandle,desc.iSerialNumber,string,sizeof(string));
      printf("OpenPilot::Servo -   Serial: %s\n",string);
      libusb_close(listHandle);
    }else{
      printf("OpenPilot::Servo -   Vendor: 0x%04X\n",desc.idVendor);
      printf("OpenPilot::Servo -  Product: 0x%04X\n",desc.idProduct);
    }
  }
}


void maestro::grabDevice(QString serialNo){
  int i, nDev, r;
  unsigned char string[256], product[256];
  libusb_device_descriptor desc;
  libusb_device_handle *listHandle;

  nDev = libusb_get_device_list(ctx, &devList);
  if (nDev==0){
    printf("OpenPilot::Servo - Failed to get device list. Cannot Continue\n");
    return;
  }

  for (i=0;i<nDev;i++){
    r=libusb_get_device_descriptor(devList[i], &desc);
    if (r!=0) continue;

    if (desc.idVendor==0x1FFB){
      if (libusb_open(devList[i],&listHandle)==0){
        libusb_get_string_descriptor_ascii(listHandle,desc.iProduct,product,sizeof(product));
        libusb_get_string_descriptor_ascii(listHandle,desc.iSerialNumber,string,sizeof(string));
        libusb_close(listHandle);
        if (serialNo.compare(QString((char*)string))==0){
          printf("OpenPilot::Servo - Device '%s' (Serial: %s) at %03i/%03i\n",
                 product, string, libusb_get_bus_number(devList[i]), libusb_get_device_address(devList[i]));
          uAct=devList[i];
          connectDevice();
          return;
        }
      }
    }
  }
}

void maestro::connectDevice(){
  unsigned char string[256];
  libusb_device_descriptor desc;

  libusb_get_device_descriptor(uAct, &desc);
  nChans=0;
  if (desc.idProduct==0x89) nChans=6;
  if (desc.idProduct==0x8A) nChans=12;
  if (desc.idProduct==0x8B) nChans=18;
  if (desc.idProduct==0x8C) nChans=24;
  if (nChans==0){
    printf("OpenPilot::Servo - Device not recognised\n");
    return;
  }
  printf("OpenPilot::Servo - Device has %i channels\n", nChans);
  channel.clear(); channel.resize(nChans); // initialise calibration data.
  
  if (libusb_open(uAct,&devHandle)==0){
    //  controlTransfer(0x80, 6, 0x0100, 0x0000, buffer);
    libusb_control_transfer(devHandle, 0x80, 6, 0x0100, 0x0000, string, sizeof(string),0);
    printf("OpenPilot::Servo - Firmware: %i.%02i\n",
           (string[13] & 0xF) + (string[13] >> 4 & 0xF) *10,
           (string[12] & 0xF) + (string[12] >> 4 & 0xF) *10);

    //Get variables to view error report.
    libusb_control_transfer(devHandle, 0xC0, 0x83, 0, 0, string, sizeof(string),0);
    printf("OpenPilot::Servo - Error 0x%03X\n",string[3]+string[4]+256);
//    printf("OpenPilot::Servo - Clearing.\n");
//    controlTransfer(0x40, (byte)uscRequest.REQUEST_CLEAR_ERRORS, 0, 0);
//    libusb_control_transfer(devHandle, 0x40, 0x86, value, servo, string, sizeof(string),0);
//    printf("OpenPilot::Servo - Get USB Connection Parameter\n");
//    r=libusb_control_transfer(devHandle, 0xC0, 0x81, 0, 1, string, sizeof(string),0);
//    printf("Bytes: %i String: %s\n", r,string);
  }
}

int maestro::channels(){
  return nChans;
}

