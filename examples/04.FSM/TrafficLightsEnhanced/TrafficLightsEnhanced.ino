#include "ClassTrafficLights.h"
#include <ParkingShield.h>

/*
 * @brief Dies ist eine Neuimplementierung der erweiteren Ampelschaltung für das Arduino UNO - Parking Schiled der Uni-Leipzig
 * Sie entstand im Rahmen eines Workshops
 * @author Michael Krause (1ux)
 *
*/

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
