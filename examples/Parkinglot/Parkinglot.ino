#include <ParkingShield.h>
#include <Scheduler.h>
#include "Parkautomat.h"

Scheduler scheduler;
ParkingShield shield(scheduler);
Parkautomat parkautomat(shield);
unsigned char counter = 0;

void setup(void)
{
  //scheduler.addTask(updateParkautomat, 1000);
}

void loop(void)
{
  scheduler.scheduleTasks();
  parkautomat.update();
}

void updateParkautomat(void * nothing)
{
  parkautomat.update();
}

