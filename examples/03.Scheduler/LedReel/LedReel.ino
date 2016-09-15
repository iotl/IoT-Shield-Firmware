#include <ParkingShield.h>
#include <Scheduler.h>
#include "Reel.h"

Scheduler scheduler;
ParkingShield shield;

Reel reel(shield);

void setup()
{
  Serial.begin(9600);
  scheduler.addTask(&reel, 100);
}

void loop()
{
  scheduler.scheduleTasks();

  if(shield.buttonS2Pressed()) reel.switchDirection(Reel::left);
  if(shield.buttonS1Pressed()) reel.switchDirection(Reel::right);
}
