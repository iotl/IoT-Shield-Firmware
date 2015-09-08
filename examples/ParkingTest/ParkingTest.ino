#include <ParkingShield.h>

ParkingShield shield;

void setup(void)
{   

}

void loop(void)
{
  bool near = shield.getBrightness() < 1000;  

  shield.setLed(ParkingShield::RED_LED, near);  
}
