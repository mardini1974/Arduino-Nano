/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>



WidgetLCD lcd(V0);

int i=0;
char XReading[9];  // 0000.000\0 pos
char YReading[9];
char ZReading[9];

char oldXReading[9];
char oldYReading[9];
char oldZReading[9];

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "529edcfccef24460aeea9d119f5a16e2";
SimpleTimer timer;
void setup()
{


  Blynk.begin(auth, "UPC243083618", "NXUKPSDD", IPAddress(192,168,178,51));
   
   
   while (Blynk.connect() == false) {
    // Wait until connected
  }


  //timer.setInterval(300L, XYZ);
  Serial.begin(115200);
}

void zeroX() { for(int x = 0; x < 9; x++) XReading[x] = 0;}
void zeroY() { for(int x = 0; x < 9; x++) YReading[x] = 0;}
void zeroZ() { for(int x = 0; x < 9; x++) ZReading[x] = 0;}

void XYZ() 
{
      lcd.print(1,0,XReading);
      lcd.print(0,0,"X");
      lcd.print(9,0,YReading);
      lcd.print(8,0,"Y");
      lcd.print(1,1,ZReading);
      lcd.print(0,1,"Z");
}
BLYNK_WRITE(V6)
{
  if (param.asInt()==1){
  Serial.write("E");
  }else {
   Serial.write("e");
  }
}
BLYNK_WRITE(V7)
{
  if (param.asInt()==1){
  Serial.write("M");
  }else {
   Serial.write("m");
  }
}
BLYNK_WRITE(V9)
{
  if (param.asInt()==1){
  Serial.write("H");
  }
}
BLYNK_WRITE(V8)
{
  if (param.asInt()==1){
  Serial.write("Q");
  }else {
   Serial.write("q");
  }
}
BLYNK_WRITE(V3)
{
  if (param[0].asInt()==1){
  Serial.write("D");
  }else if(param[0].asInt()==-1) {
   Serial.write("A");
  }else{
   Serial.write("a");
   Serial.write("d");
  }
  if (param[1].asInt()==1){
  Serial.write("W");
  }else if(param[1].asInt()==-1) {
   Serial.write("S");
  }else{
   Serial.write("w");
   Serial.write("s");
  }
}
BLYNK_WRITE(V4)
{
  if (param.asInt()==1){
  Serial.write("T");
  }else {
   Serial.write("t");}}
   
BLYNK_WRITE(V5)
{
  if (param.asInt()==1){
  Serial.write("G");
  }else {
   Serial.write("g");}}

BLYNK_WRITE(V2)
{
  Serial.write(param.asStr());
}
      


void loop()
{
  Blynk.run();
  timer.run();
  int x;
char ch, ky;
 
    if(Serial.available() >= 8)
        {
        ch = Serial.read();
        switch(ch)
            {
              Serial.write(ch);
            case 'X':
                    while(Serial.available() < 7)
                        delay(10);
                    for(x = 0; x < 7; x++)
                        XReading[x] = Serial.read();
                    if(strncmp(XReading, oldXReading, 7) != 0)
                        {
                        
                        strcpy(oldXReading, XReading);
                        }
                    //zeroX();
                    break;                    
            
            case 'Y':
                    while(Serial.available() < 7)
                        delay(10);
                    for(x = 0; x < 7; x++)
                        YReading[x] = Serial.read();
                    if(strncmp(YReading, oldYReading, 7) != 0)
                        {
                       strcpy(oldYReading, YReading);
                        }
                    //zeroY();
                    break;                    

            case 'Z':
                    while(Serial.available() < 7)
                        delay(10);
                    for(x = 0; x < 7; x++)
                        ZReading[x] = Serial.read();
                    if(strncmp(ZReading, oldZReading, 7) != 0)
                        {    
                       strcpy(oldZReading, ZReading);
                        }
                    //zeroZ();
                    break;
  
            default:
                    break;

            }
        }
    

}
