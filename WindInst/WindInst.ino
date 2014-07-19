#include "aydpTime.h"
#include "aydpCommsProtocol.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(5,6); // Rx pin D5 Tx pin D6
aydpTime localTime;
aydpCommsProtocol comms;
volatile unsigned long int pSpdPulseTime;
volatile unsigned long int spdPulseDelta;
float windSpeed, windDir;

void setup(){
  // Setup Bluetooth and set device PIN and name
  bluetooth.begin(9600);
  bluetooth.println("AT+PIN1234");
  delay(50);
  bluetooth.write("AT+NAMEWindInst");
  delay(50);

  Serial.begin(115200);
  pSpdPulseTime=0;
  spdPulseDelta=1e12;
  windSpeed=0;
  windDir=0;
  setupDirection();
  // Attach interrupt to ISR to handle
  // reading wind speed on pin 2 (Interrupt 0)
  pinMode(2, INPUT);
  attachInterrupt(0,speedPulseRising,RISING);
  // Make A0 an analogue input so we can read direction-related
  // voltage.
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
  localTime.resetArduinoTime(micros());
/*  
  Serial.println("Data Sizes (bytes):");
  Serial.print("unsigned char");
  Serial.println(sizeof(unsigned char));
  Serial.print("unsigned int");
  Serial.println(sizeof(unsigned int));
  Serial.print("int");
  Serial.println(sizeof(int));
  Serial.print("unsigned long int");
  Serial.println(sizeof(unsigned long int));
  Serial.print("float");
  Serial.println(sizeof(float));
*/
  
}

void loop(){
  float calcSpeed, calcDir;
  uint8_t message[256];
  // Set a maximum timeout on pulse length so the reading drops back to 0 properly.
  // Get correct time
  localTime.incrementByMicros(micros());
/*
  Serial.print("Time: ");
  Serial.print(localTime.year);
  Serial.print(".");
  Serial.print(localTime.day);
  Serial.print(".");
  Serial.print(localTime.hour);
  Serial.print(".");
  Serial.print(localTime.min);
  Serial.print(".");
  Serial.print(localTime.sec);
  Serial.print("-");
  Serial.println(localTime.micro);
*/
//  Serial.println(digitalRead(2));
//  Serial.print("spdPulseDelta ");
//  Serial.print(spdPulseDelta);
//  Serial.println(" uS");
  calcSpeed=1.0e6/(float)spdPulseDelta * 1.492; // 1.492 MPH/Hz
  if (calcSpeed>0.01 && calcSpeed<100) windSpeed=calcSpeed;
  if (pSpdPulseTime<micros()-5e6) windSpeed=0;
  
  calcDir=calcDirection();
  if (calcDir>-.001) windDir=calcDir;
/*
  Serial.print("Wind Speed ");
  Serial.print(windSpeed);
  Serial.print(" MPH      Direction: ");
  Serial.print(windDir);
  Serial.println(" deg");
*/
  comms.createWindMessage(localTime, windSpeed, windDir);
  // Copy comms packet into suitable memory space for Arduino to transmit...
  memcpy(message,&comms.header, sizeof(comms.header));
  bluetooth.write(message, sizeof(comms.header));
/*
  Serial.print("Message length ");
  Serial.print(sizeof(comms.header)+comms.header.length+sizeof(comms.checksum));
  Serial.println(" bytes");
  int i;
  for (i=0;i<sizeof(comms.header);i++){
    Serial.print(message[i]);
    Serial.print(" ");
  }
  Serial.print("- ");
*/
  memcpy(message, comms.data, comms.header.length);
  bluetooth.write(message, comms.header.length);
  bluetooth.write(comms.checksum);
/*
  for (i=0;i<comms.header.length;i++){
    Serial.print(message[i]);
    Serial.print(" ");
  } 
*/  
//  Serial.println("");
//  Serial.print("A5 = ");
//  Serial.println(analogRead(A5));
  if (bluetooth.available())  Serial.write(bluetooth.read());
  if (Serial.available())  bluetooth.write(Serial.read());
  delay(20);
}

float rangeCentre[16];
float rangeValue[16];

/*
Direction 0.00  Resistance 33000  Range Centre 876.35
Direction 22.50  Resistance 6570  Range Centre 554.63
Direction 45.00  Resistance 8320  Range Centre 613.81
Direction 67.50  Resistance 891  Range Centre 141.43
Direction 90.00  Resistance 1000  Range Centre 156.10
Direction 112.50  Resistance 688  Range Centre 112.76
Direction 135.00  Resistance 2200  Range Centre 290.31
Direction 157.50  Resistance 1410  Range Centre 207.15
Direction 180.00  Resistance 3900  Range Centre 422.16
Direction 202.50  Resistance 3140  Range Centre 369.58
Direction 225.00  Resistance 16000  Range Centre 759.93
Direction 247.50  Resistance 14120  Range Centre 734.70
Direction 270.00  Resistance 54464  Range Centre 929.15
Direction 292.50  Resistance 42120  Range Centre 904.59
Direction 315.00  Resistance 64900  Range Centre approx 944
Direction 337.50  Resistance 21880  Range Centre 816.51
*/

void setupDirection(){
  int i;
  for (i=0;i<16;i++) rangeValue[i]=22.5*(float)i; // Values 0 to 337.5 in steps of 22.5 degrees
  rangeCentre[0]=870;          //   0.0 deg
  rangeCentre[1]=555;          //  22.5 deg
  rangeCentre[2]=610;          //  45.0 deg
  rangeCentre[3]=150;          //  67.5 deg
  rangeCentre[4]=157;          //  90.0 deg
  rangeCentre[5]=113;          // 112.5 deg
  rangeCentre[6]=290;          // 135.0 deg
  rangeCentre[7]=207;          // 157.5 deg
  rangeCentre[8]=425;          // 180.0 deg
  rangeCentre[9]=369;          // 202.0 deg
  rangeCentre[10]=760;         // 225.0 deg
  rangeCentre[11]=739;         // 247.5 deg
  rangeCentre[12]=980;         // 270.0 deg
  rangeCentre[13]=911;         // 292.5 deg
  rangeCentre[14]=939;         // 315.0 deg
  rangeCentre[15]=950;         // 337.5 deg
/*  
  for (i=0;i<16;i++){
    Serial.print("Direction ");
    Serial.print(rangeValue[i]);
    Serial.print("  Range Centre ");
    Serial.println(rangeCentre[i]);
  }
  */
}

float calcDirection(){
  int i;
  int dirValue=analogRead(A0);
  int hRW=15; // half-range width;
  for (i=0;i<16;i++){
    if (dirValue>rangeCentre[i]-hRW && dirValue<rangeCentre[i]+hRW){
      return rangeValue[i];
    }
  }
//  Serial.print("Direction Value ");
//  Serial.print(dirValue);
//  Serial.println(" not found");
  return -1;
}

void speedPulseRising(){
  unsigned long int cSpdPulseTime;
  unsigned long int delta;
  cSpdPulseTime=micros();
  delta=cSpdPulseTime-pSpdPulseTime;
  if (delta>200){
    spdPulseDelta=delta;
    pSpdPulseTime=cSpdPulseTime;
  }
}
