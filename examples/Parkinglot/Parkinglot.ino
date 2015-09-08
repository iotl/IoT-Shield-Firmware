#include <ParkingShield.h>
#include <Scheduler.h>
#include "Parkautomat.h"

Scheduler scheduler;
ParkingShield shield(scheduler);
Parkautomat parkautomat(shield);
unsigned char counter = 0;

void setup(void)
{
    scheduler.addTask(updateFSM, 1000);
}

void loop(void)
{
  buttonS1Handler();
  buttonS2Handler();
  scheduler.scheduleTasks();
}

void updateFSM(void * nothing)
{
  parkautomat.updateState();
}

bool taster1 = false;

bool getTaster()
{
  if(taster1)
  {
    taster1 = false;
    return true;
  }
  return false;
}

void buttonS1Handler(void)
{ 
    static unsigned long int millisForButtonLock = 0;
    static bool buttonS1Locked = false;
    
    if (millisForButtonLock < millis())
    buttonS1Locked = false;
    
    if (shield.buttonS1Pressed() && !buttonS1Locked)
    {
      taster1 = true;
    counter = ++counter % 10;
      millisForButtonLock = millis() + 250;
      buttonS1Locked = true;
    }
}

void buttonS2Handler(void)
{
  if (shield.buttonS2Pressed())
    counter = 0;
}

