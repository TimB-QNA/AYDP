#include "channel.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>

union{
  unsigned int data;
  byte array[2];
}convU16;

unsigned int battery; // millivolts
bool writeToEEProm;

channel jibChan;
channel mainChan;
channel rudderChan;

Servo jibServo;
Servo mainServo;
Servo rudderServo;

unsigned long int lastAnalogue;
unsigned long int lastServo;

SoftwareSerial debug(A0,A1); // Rx, Tx

void setup(){
  writeToEEProm=false;

  jibServo.attach(5);
  mainServo.attach(6);
  rudderServo.attach(7);
  
  Wire.begin(0x08);
  Wire.onReceive(iicReceiveEvent);
  Wire.onRequest(iicRequestEvent);
  lastAnalogue=0;
  lastServo=0;
  debug.begin(115200);
}

void loop(){
  if (millis()>lastAnalogue+10000){
    lastAnalogue=millis();
    battery=analogRead(7)*(3300./1024.)*8+0.5;
    debug.print("Battery Voltage: "); 
    debug.print(battery);
    debug.println(" mV");
  }

  if (millis()>lastServo+50){
    lastServo=millis();
    jibServo.writeMicroseconds(jibChan.value());
    mainServo.writeMicroseconds(mainChan.value());
    rudderServo.writeMicroseconds(rudderChan.value());
  }

  if (jibChan.changed) jibServo.writeMicroseconds(jibChan.value());
  if (mainChan.changed) mainServo.writeMicroseconds(mainChan.value());
  if (rudderChan.changed) rudderServo.writeMicroseconds(rudderChan.value());
}

/* Addressing:
 *   0 is reserved
 *   1 is battery voltage
 *   2 to 6 are analogue channels (read only)
 */
void iicReceiveEvent(int howMany){
  byte bRead;
  byte address;
  int i;

  if (howMany==1) return;

  address=Wire.read();
  debug.print("RX - Address ");
  debug.println(address);
  
  // Assuming there is data available, process the set request.
  if (address==0x10){
    // Set Jib position
    convU16.array[0]=Wire.read();
    convU16.array[1]=Wire.read();
    jibChan.set(convU16.data);
  }
  if (address==0x11){
    // Set Main position
    convU16.array[0]=Wire.read();
    convU16.array[1]=Wire.read();
    mainChan.set(convU16.data);
  }
  if (address==0x12){
    // Set Rudder position
    convU16.array[0]=Wire.read();
    convU16.array[1]=Wire.read();
    
    debug.print("Bytes ");
    debug.print(convU16.array[0],HEX);
    debug.print(" ");
    debug.println(convU16.array[1],HEX);

    rudderChan.set(convU16.data);
    debug.print("Rudder Position Set to ");
    debug.println(rudderChan.setPoint);
  }

  // Handle any "command" messages which require only the address
  if (address==0xFF){
    writeToEEProm=(Wire.read()==0xFF);
  }
  
  // If data remaining read remaining data to prevent interface from being confused...
  while(Wire.available()) Wire.read();
  
}

void iicRequestEvent(){
  byte address;
  if (Wire.available()==0) return;

  address=Wire.read();
  debug.print("Address ");
  debug.println(address);
  
  if (address==1){
//    debug.println(battery);
    convU16.data=battery;
    Wire.write(convU16.array[1]);
    Wire.write(convU16.array[0]);
    return;
  }
}

