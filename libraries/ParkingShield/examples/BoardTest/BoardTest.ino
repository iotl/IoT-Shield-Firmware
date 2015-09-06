#include <ParkingShield.h>
#include <SevenSeg.h>
#include <DeviceArduino.h>
#include <Scheduler.h>


ParkingShield shield;
unsigned char counter = 0;

void setup()
{
    Serial.begin(9600);
    Scheduler::init();
    Scheduler::addTask(output, 1000);
    shield.sevenSeg().showDecimalPoint();
    playMelody();
}

void loop()
{
	buttonS1Handler();
	buttonS2Handler();
	showNumber(counter);
  Scheduler::scheduleTasks();
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
	shield.sevenSeg().showNumber(counter);
	
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

void playMelody(void)
{
  static int length = 15; // the number of notes
  static char notes[] = "ccggaagffeeddc "; // a space represents a rest
  static int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
  static int tempo = 300;
  
  for (int i = 0; i < length; i++)
  {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
}

void playTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    shield.setBuzzer(true);
    delayMicroseconds(tone);
    shield.setBuzzer(false);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration)
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++)
  {
    if (names[i] == note)
      playTone(tones[i], duration);
  }
}

