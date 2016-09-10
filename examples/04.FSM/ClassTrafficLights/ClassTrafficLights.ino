#include <ParkingShield.h>
#include "ClassTrafficLights.h"

/*
 * @brief Dies ist eine Neuimplementierung des Ampel-Zustandsautomaten für das Arduino UNO - Parking Schiled der Uni-Leipzig
 * Er entstand im Rahmen eines Workshops.
 * Der Zustandsautomat liegt als grafische Übersicht bei. Dieser bildet die Spezifikation.
 * @author Michael Krause (1ux)
 *
*/

void ClassTrafficLights::Prozess(Alphabet Ereignis)
{
    this->Zustand = Ueberfuehrungsfunktion[Zustand][Ereignis];

  switch(this->Zustand)
  {
    case S0: 
              _shield.setLed(ParkingShield::RED_LED,true);
              _shield.setLed(ParkingShield::YELLOW_LED,false);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              break;

    case S1: 
              _shield.setLed(ParkingShield::RED_LED,true);
              _shield.setLed(ParkingShield::YELLOW_LED,true);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              break;

    case S2: 
              _shield.setLed(ParkingShield::RED_LED,false);
              _shield.setLed(ParkingShield::YELLOW_LED,false);
              _shield.setLed(ParkingShield::GREEN_LED,true);
              break;

    case S3: 
              _shield.setLed(ParkingShield::RED_LED,false);
              _shield.setLed(ParkingShield::YELLOW_LED,true);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              break;
  }
    
}
