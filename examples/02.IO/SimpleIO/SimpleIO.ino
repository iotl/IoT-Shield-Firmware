#include <ParkingShield.h>

ParkingShield shield;
int True_Counter=0;
bool pressed=false;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(shield.buttonS1Pressed())
  {
    shield.setLed(ParkingShield::RED_LED, true);
    True_Counter++;
    Serial.println(True_Counter);
    shield.setRepeatInterval(500);
  }
  
  
}
