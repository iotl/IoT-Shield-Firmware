#include <ParkingShield.h>
#include <Scheduler.h>

#include "Parkinglot.h"
#include "Thingspeak.h"

Scheduler scheduler;
ParkingShield shield;
Parkinglot parkinglot(shield);

SoftwareSerial espSerial(2, 3);
Esp8266<SoftwareSerial> esp(espSerial);

Talkback talkback(espSerial, esp, parkinglot, 10251, "I9FW4PFTGV8X55FG");

/**
 * @brief Dies ist eine Neuimplementierung der Parkbucht für das Arduino UNO - Parking Schiled der Uni-Leipzig
 * Der überarbeitete Zustandsautomat liegt als grafische Übersicht bei. Dieser bildet die Spezifikation.
 * @author Michael Krause (1ux)
 **/

void setup(void)
{
  Serial.begin(9600);

  setupWlan(esp, "eduinfo", "");

  shield.setRepeatInterval(250);
  scheduler.addTask(&parkinglot, 4000, true);
  scheduler.addTask(&talkback, 5000, true);
}

void loop(void)
{
  scheduler.scheduleTasks();
  if(shield.getBrightness() < 700)
  {
    parkinglot.process(Parkinglot::ready);
    if(shield.buttonS1Pressed())
    {
      parkinglot.process(Parkinglot::pay);
    }
    else if(shield.buttonS2Pressed())
    {
      parkinglot.process(Parkinglot::start);
    }
  }
  else
  {
    parkinglot.process(Parkinglot::free);
  }
}

