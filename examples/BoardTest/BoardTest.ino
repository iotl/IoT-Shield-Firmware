#include <ParkingShield.h>
#include <Scheduler.h>

ParkingShield shield;
unsigned char counter = 0;

void setup(void)
{
    Serial.begin(9600);
    Scheduler::init();
    Scheduler::addTask(output, 1000);
    shield.showDecimalPoint();
    shield.showNumber(9);
    shield.countDown();
    shield.playMarch();
    //shield.playMelody();
}

void loop(void)
{
	buttonS1Handler();
	buttonS2Handler();
	showNumber(counter);
  Scheduler::scheduleTasks();
  shield.update();
}

void output(void)
{
    Serial.print("Button S1: ");
    Serial.println(shield.buttonS1Pressed());
    Serial.print("Button S2: ");
    Serial.println(shield.buttonS2Pressed());
    Serial.print("Licht: ");
    Serial.println(shield.getBrightness());
    Serial.print("Temperatur: ");
    Serial.print(shield.getTemperature());
    Serial.println(" Grad Celsius");
}

void buttonS1Handler(void)
{	
    static unsigned long int millisForButtonLock = 0;
	  static bool buttonS1Locked = false;
    
    if (millisForButtonLock < millis())
		buttonS1Locked = false;
    
    if (shield.buttonS1Pressed() && !buttonS1Locked)
    {
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

void showNumber(unsigned char counter)
{
	shield.showNumber(counter);
	
	if (counter < 8)
	{
		if (0b001 & counter)
			shield.setLed(ParkingShield::GREEN_LED, true);
		else
			shield.setLed(ParkingShield::GREEN_LED, false);
	
		if (0b010 & counter)
			shield.setLed(ParkingShield::YELLOW_LED, true);
		else
			shield.setLed(ParkingShield::YELLOW_LED, false);
	
		if (0b100 & counter)
			shield.setLed(ParkingShield::RED_LED, true);
		else
			shield.setLed(ParkingShield::RED_LED, false);
	}
}

