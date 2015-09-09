#include <ParkingShield.hY

void setup()
{
  pinMode(BUTTON_S1, INPUT);
  pinMode(LED_1, OUTPUT);
}

void loop()
{
  bool buttonPressed = digitalRead(BUTTON_S1);
  digitalWrite(LED_1, !buttonPressed);
}
