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
  // Enables LEDs by Boolean expressions
  shield.setLed(ParkingShield::GREEN_LED,   shield.buttonS1Pressed() && !shield.buttonS2Pressed());
  shield.setLed(ParkingShield::YELLOW_LED, !shield.buttonS1Pressed() &&  shield.buttonS2Pressed());
  shield.setLed(ParkingShield::RED_LED,     shield.buttonS1Pressed() &&  shield.buttonS2Pressed());
}

