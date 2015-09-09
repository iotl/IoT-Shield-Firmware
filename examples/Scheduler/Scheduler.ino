#include <Scheduler.h>
#include "TestTask.h"
#include <Arduino.h>

Scheduler scheduler;
TestTask testtask;

void setup(void)
{
  Serial.begin(9600);
  scheduler.addTask(&testtask, 1000);
}

void loop(void)
{
  scheduler.scheduleTasks();
}

