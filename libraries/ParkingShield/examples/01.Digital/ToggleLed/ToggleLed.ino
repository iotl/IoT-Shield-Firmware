#include <DeviceArduino.h>
#include <ParkingShield.h>
#include <SevenSeg.h>

ParkingShield shield;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{  
  static bool enable = false;
  enable = !enable;
  
  shield.setLed(ParkingShield::GREEN_LED, enable);

  delay(1000);  
}

void buttonS1Handler(bool enableLed)
{
  
}

