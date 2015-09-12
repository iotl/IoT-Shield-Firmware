#include <Scheduler.h>
#include "TestTask.h"

Scheduler scheduler;
TestTask testtask;
unsigned char const MAX_ELEMENTS = 10;
int numbers[MAX_ELEMENTS];

void setup(void)
{
  Serial.begin(9600);
  scheduler.addTask(&testtask, 2000);
  scheduler.addTask(testtaskRemover, 1000);

  for (unsigned char i = 0; i < MAX_ELEMENTS; i++)
  	numbers[i] = 1;
}

void loop(void)
{
  scheduler.scheduleTasks();
}

void testtaskRemover(void)
{
  static int i = 10;

  if (scheduler.taskExists(testtaskRemover))
  	Serial.println("testtaskRemover active");

  if (i <= 0)
  	scheduler.removeTask(&testtask);
  else
  {
    if (scheduler.taskExists(&testtask))
      Serial.println("Removing testtask in: " + String(i) + " seconds.");
  }

  if (i <= -2)
  {
  	Serial.println("Time is over, removing testtaskRemover from scheduler");
  	scheduler.removeTask(testtaskRemover);
  	Serial.println("Adding testtaskWithData to scheduler");
  	scheduler.addTask(testtaskWithData, numbers, 1000);
  }

  i--;
}

void testtaskWithData(void * data)
{
  static int i = 0;

  int * const myData = static_cast<int * const>(data);

  if (scheduler.taskExists(testtaskWithData))
    Serial.println("Executing testtaskWithData");

  Serial.println("Array content:");
  for (unsigned char i = 0; i < MAX_ELEMENTS; i++)
  {
  	Serial.print(String(myData[i]) + " ");
  	myData[i] += i;
  }
  Serial.println("");

  if (i == MAX_ELEMENTS)
  {
    Serial.println("Time is over, removing testtaskWithData from scheduler");
    scheduler.removeTask(testtaskWithData);
  }

  i++;
}
