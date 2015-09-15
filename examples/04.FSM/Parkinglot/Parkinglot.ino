#include <ParkingShield.h>
#include <Scheduler.h>
#include "Parkautomat.h"

Scheduler scheduler;
ParkingShield shield;
Parkautomat parkautomat(shield, scheduler);

void setup(void)
{
    shield.setRepeatInterval = 250;
}

void loop(void)
{
  scheduler.scheduleTasks();
  parkautomat.update();
}

