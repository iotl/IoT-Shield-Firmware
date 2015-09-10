#include <ParkingShield.h>

ParkingShield shield;

void setup() 
{ }

void loop()
{  
  static bool enable = false;
  enable = !enable;
  
  shield.setLed(ParkingShield::GREEN_LED, enable);

  shield.setLed(ParkingShield::GREEN_RED, enable);

  shield.setLed(ParkingShield::GREEN_LED, enable);

 
}
