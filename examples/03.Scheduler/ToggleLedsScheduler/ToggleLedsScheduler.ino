#include <ParkingShield.h>
#include <Scheduler.h>

ParkingShield shield;
Scheduler sched;

void setup() 
{
  sched.addTask(toggleRedLed, 1000);
  sched.addTask(toggleYellowLed, 500);
  shield.setDebounceInterval(0);
}

void loop()
{
  sched.scheduleTasks();
  shield.setLed(ParkingShield::GREEN_LED, shield.buttonS1Pressed());
}

void toggleRedLed(void)
{
	static bool ledEnabled = true;

	shield.setLed(ParkingShield::RED_LED, ledEnabled);

	ledEnabled = !ledEnabled;
}

void toggleYellowLed(void)
{
	static bool ledEnabled = true;

	shield.setLed(ParkingShield::YELLOW_LED, ledEnabled);

	ledEnabled = !ledEnabled;
}