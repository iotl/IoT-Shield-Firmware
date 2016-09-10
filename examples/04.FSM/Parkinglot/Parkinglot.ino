#include <ParkingShield.h>
#include <Scheduler.h>
#include "ClassParkinglot.h"

Scheduler scheduler;
ParkingShield shield;
ClassParkinglot parkinglot(shield);

/*
 * @brief Dies ist eine Neuimplementierung der Parkbucht für das Arduino UNO - Parking Schiled der Uni-Leipzig
 * Der überarbeitete Zustandsautomat liegt als grafische Übersicht bei. Dieser bildet die Spezifikation.
 * @author Michael Krause (1ux)
 *
*/


void setup(void)
{
    shield.setRepeatInterval(250);
    Serial.begin(9600);
}

void loop(void)
{
   if(shield.getBrightness()<450)
   {
         parkinglot.Prozess(ClassParkinglot::ready);
         if(shield.buttonS1Pressed())
         {
            parkinglot.Prozess(ClassParkinglot::pay);
         }
         if(shield.buttonS2Pressed())
         {
            parkinglot.Prozess(ClassParkinglot::start);
            
         }
   }
   else parkinglot.Prozess(ClassParkinglot::free);
}

