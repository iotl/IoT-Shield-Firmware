#include <DeviceArduino.h>
#include <ParkingShield.h>
#include <SevenSeg.h>


ParkingShield shield;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.print(F("Light intensity is : " ));
  Serial.print(shield.getBrightness() / 1024. * 100);
  Serial.print(" %% \n");

  delay(1000);
}
