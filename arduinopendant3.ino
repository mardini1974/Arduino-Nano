
#include <SoftwareSerial.h>





SoftwareSerial JYmcu(3,2); 
void setup() 
{
    Serial.begin(115200);
    JYmcu.begin (115200);
    
    
    Serial.write ('E');
 
}

void loop() 
{
;
char ch, ky;
        
    if(Serial.available() >= 1)
        {
        char ch = Serial.read();
        JYmcu.print(ch);
        }               
    if(JYmcu.available() >= 1)
        {
      char ky=JYmcu.read();
        Serial.print (ky);
  
       }    
}



