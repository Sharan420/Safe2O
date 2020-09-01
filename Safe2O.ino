#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"
Adafruit_SGP30 sgp;
static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;
float calibration_value = 21.34;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial mySerial(3, 2);
void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  mySerial.begin(9600);
  mySerial.println("AT"); 
  mySerial.println("AT+CSQ"); 
  mySerial.println("AT+CCID"); 
  mySerial.println("AT+CREG?"); 
}

void loop() {
  if (getPH() <= 6.5 or getPH() >= 8.5){
    sendsms()
  }
  else{
  }

}

char latandlong()
{
  if (gps.location.isValid())
  {
    char a = String(gps.location.lat())
    char b = String(gps.location.lng())
    return a+b
    
  }
  else
  {
    Serial.print(F("INVALID"));
  }
}

int getPH() 
{
  for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 return ph_act
}
}

float tvocget(){
if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
return sgp.TOVC
}

float eCO2get(){
if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
return sgp.eCO2
}

void sendsms(){
  mySerial.println("AT+CMGF=1");
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"");
  mySerial.print("PH IS TOO HIGH IT IS:");
  mySerial.print(getPH());
  mySerial.print("TVOC:");
  mySerial.print(tvocget());
  mySerial.print("eCO2:");
  mySerial.print(eCO2get());
  mySerial.write(26);
}
