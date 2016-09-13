#include <ParkingShield.h>
#include <Scheduler.h>
#include "ClassParkinglot.h"

Scheduler scheduler;
ParkingShield shield;
ClassParkinglot parkinglot(shield);

/**
 * @brief Dies ist eine Neuimplementierung der Parkbucht für das Arduino UNO - Parking Schiled der Uni-Leipzig
 * Der überarbeitete Zustandsautomat liegt als grafische Übersicht bei. Dieser bildet die Spezifikation.
 * @author Michael Krause (1ux)
 **/

void setup(void)
{
  shield.setRepeatInterval(250);
  scheduler.addTask(&parkinglot, 1000, true);
}

void loop(void)
{
  scheduler.scheduleTasks();
  if(shield.getBrightness() < 700)
  {
    parkinglot.process(ClassParkinglot::ready);
    if(shield.buttonS1Pressed())
    {
      parkinglot.process(ClassParkinglot::pay);
    }
    else if(shield.buttonS2Pressed())
    {
      parkinglot.process(ClassParkinglot::start);
    }
  }
  else
  {
    parkinglot.process(ClassParkinglot::free);
  }
}

