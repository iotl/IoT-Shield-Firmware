#include <ParkingShield.h>
ParkingShield shield;

void setup()
{ }

void loop()
{
  // Enables LEDs by Boolean expressions
  shield.setLed(ParkingShield::GREEN_LED,   shield.buttonS1Pressed() && !shield.buttonS2Pressed());
  shield.setLed(ParkingShield::YELLOW_LED, !shield.buttonS1Pressed() &&  shield.buttonS2Pressed());
  shield.setLed(ParkingShield::RED_LED,     shield.buttonS1Pressed() &&  shield.buttonS2Pressed());
}
