#include <ParkingShield.h>

ParkingShield shield;
//const int ledPin = 3;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.print(F("Light intensity is : " ));
  Serial.println(shield.getBrightness() / 1024. * 100);
  
  
  
  delay(1000);
}
