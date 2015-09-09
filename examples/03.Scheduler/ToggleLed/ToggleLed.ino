#include <ParkingShield.h>

ParkingShield shield;

void setup() 
{
  Serial.begin(9600);
}

void loop()
{  
  static bool enable = false;
  enable = !enable;
  
  shield.setLed(ParkingShield::GREEN_LED, enable);

  delay(1000);  
}
