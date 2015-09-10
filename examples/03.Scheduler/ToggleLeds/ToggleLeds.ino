#include <ParkingShield.h>
ParkingShield shield;

void setup() 
{ }

void loop()
{
  shield.setLed(ParkingShield::RED_LED, true);
  shield.setLed(ParkingShield::YELLOW_LED, true);
  delay(500);
  
  shield.setLed(ParkingShield::YELLOW_LED, false);
  delay(500);
  
  shield.setLed(ParkingShield::RED_LED, false);
  shield.setLed(ParkingShield::YELLOW_LED, true);
  delay(500);
  
  shield.setLed(ParkingShield::YELLOW_LED, false);
  delay(500);

  // Very long time insensitive
  shield.setLed(ParkingShield::GREEN_LED, shield.buttonS1Pressed());
}
