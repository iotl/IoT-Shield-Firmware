#include "ClassTrafficLights.h"
#include <ParkingShield.h>

ParkingShield shield;
ClassTrafficLights TrafficLight(shield);

void setup() 
{
  shield.setRepeatInterval(250);

}

void loop() 
{
  if(shield.buttonS1Pressed()) TrafficLight.Prozess(ClassTrafficLights::tick);
  //Prozess(tick);
  if(shield.buttonS2Pressed()) TrafficLight.Prozess(ClassTrafficLights::reset);
  //Prozess(reset);

}
