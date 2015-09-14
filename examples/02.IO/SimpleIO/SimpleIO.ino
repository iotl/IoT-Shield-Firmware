#include <ParkingShield.h>

ParkingShield shield;

void setup()
{
  shield.setDebounceInterval(0);
}

void loop()
{
  bool buttonPressed = shield.buttonS1Pressed();
  shield.setLed(ParkingShield::RED_LED, buttonPressed);
}
