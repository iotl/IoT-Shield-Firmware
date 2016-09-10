#include <ParkingShield.h>
#include "ClassTrafficLights.h"


void ClassTrafficLights::Prozess(Alphabet Ereignis)
{
    this->Zustand = Ueberfuehrungsfunktion[Zustand][Ereignis];

  switch(this->Zustand)
  {
    case S0: 
              _shield.setLed(ParkingShield::RED_LED,false);
              _shield.setLed(ParkingShield::YELLOW_LED,false);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              _shield.sevenSeg.showNumber(0);
              break;
              
    case S1: 
              _shield.setLed(ParkingShield::RED_LED,true);
              _shield.setLed(ParkingShield::YELLOW_LED,false);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              _shield.sevenSeg.showNumber(1);
              break;

    case S2: 
              _shield.setLed(ParkingShield::RED_LED,true);
              _shield.setLed(ParkingShield::YELLOW_LED,true);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              _shield.sevenSeg.showNumber(2);
              break;

    case S3: 
              _shield.setLed(ParkingShield::RED_LED,false);
              _shield.setLed(ParkingShield::YELLOW_LED,false);
              _shield.setLed(ParkingShield::GREEN_LED,true);
              _shield.sevenSeg.showNumber(3);
              break;

    case S4: 
              _shield.setLed(ParkingShield::RED_LED,false);
              _shield.setLed(ParkingShield::YELLOW_LED,true);
              _shield.setLed(ParkingShield::GREEN_LED,false);
              _shield.sevenSeg.showNumber(4);
              break;
  }
    
}
