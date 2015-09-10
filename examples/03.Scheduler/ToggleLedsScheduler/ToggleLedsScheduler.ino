#include <ParkingShield.h>
#include <Scheduler.h>
#include "LedTask.h"

ParkingShield shield;
Scheduler sched;

LedTask redTask(ParkingShield::RED_LED, shield);
LedTask yellowTask(ParkingShield::YELLOW_LED, shield);

void setup() 
{
  sched.addTask(&redTask, 1000, true);
  sched.addTask(&yellowTask, 500, true);    
}

void loop()
{
  sched.scheduleTasks();  
}
