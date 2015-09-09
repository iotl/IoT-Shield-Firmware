#include <ParkingShield.h>

ParkingShield shield;

void setup()
{ }

void loop()
{
  bool buttonPressed = shield.buttonS1Pressed();
  shield.setLed(RED_LED, buttonPressed);
}
