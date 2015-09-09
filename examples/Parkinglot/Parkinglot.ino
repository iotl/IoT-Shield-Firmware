#include <ParkingShield.h>
#include <Scheduler.h>
#include "Parkautomat.h"

Scheduler scheduler;
ParkingShield shield;
Parkautomat parkautomat(shield, scheduler);

void setup(void)
{
}

void loop(void)
{
  scheduler.scheduleTasks();
  parkautomat.update();
}

