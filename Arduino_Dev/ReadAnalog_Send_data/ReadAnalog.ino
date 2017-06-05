/*
  # Example code for the moisture sensor
  # Editor     : Lauren
  # Date       : 13.01.2012
  # Version    : 1.0
  # Connect the sensor to the A0(Analog 0) pin on the Arduino board
  
  # the sensor value description
  # 0  ~300     dry soil
  # 300~700     humid soil
  # 700~950     in water
*/
// me use arduino UNO
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,2);
float mvalue, tvalue;
float mmvalue,ttvalue;
void setup(){
  
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop(){
   mvalue = analogRead(A0);
  Serial.print("Moisture Sensor Value:");
  Serial.println(mmvalue); 
  Serial.print("\n"); 
  delay(1000);
  tvalue = analogRead(A1);
  Serial.print("Moisture Sensor mValue:");
  Serial.println(ttvalue); 
  delay(1000);
  Serial.print("\n"); 
  Serial.print("\n"); 
  Serial.print("\n");
  String M;
  String T;
 // String mmvalue = String(mvalue)+"\r\n";
   mmvalue = (mvalue/1024)*100;
   ttvalue = (tvalue/1024)*50;
   String msg="MC"+String(mmvalue);
   String msg2="TP"+String(ttvalue);
  mySerial.println(msg);
  mySerial.println(msg2);
  
  delay(1000);
  if (mySerial.available()) {
    Serial.println(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.println(mvalue);
  }
  delay(1000);
  
}
