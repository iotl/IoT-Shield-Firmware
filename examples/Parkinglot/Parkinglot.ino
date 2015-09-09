#include <ParkingShield.h>
#include <Scheduler.h>
#include "Parkautomat.h"

Scheduler scheduler;
ParkingShield shield(scheduler);
Parkautomat parkautomat(shield);
unsigned char counter = 0;

void setup(void)
{
}

void loop(void)
{
  scheduler.scheduleTasks();
  parkautomat.update();
}

