#include <ParkingShield.h>
#include "ClassParkinglot.h"



void ClassParkinglot::Prozess(Alphabet Ereignis)
{
  this->Zustand = Ueberfuehrungsfunktion[Zustand][Ereignis];
  _shield.setRepeatInterval(250);
  
  switch(Zustand)
  {
       case S0: 
           _shield.setLed(ParkingShield::RED_LED,false);
           _shield.setLed(ParkingShield::YELLOW_LED,false);
           _shield.setLed(ParkingShield::GREEN_LED,false);
           credit=0;
           _shield.sevenSeg.clear();
           break;
       case S1: 
           _shield.setLed(ParkingShield::RED_LED,true);
           _shield.setLed(ParkingShield::YELLOW_LED,false);
           _shield.setLed(ParkingShield::GREEN_LED,false);
           credit=0;
           _shield.sevenSeg.showNumber(credit);
           break;
       case S2: 
           _shield.setLed(ParkingShield::RED_LED,true);
           _shield.setLed(ParkingShield::YELLOW_LED,false);
           _shield.setLed(ParkingShield::GREEN_LED,false);
           if(credit!=1) credit=1;
           _shield.sevenSeg.showNumber(credit);
           break;
       case S3: 
           _shield.setLed(ParkingShield::RED_LED,true);
           _shield.setLed(ParkingShield::YELLOW_LED,false);
           _shield.setLed(ParkingShield::GREEN_LED,false);
           if(_shield.buttonS1Pressed() && credit <9) credit++;
           _shield.sevenSeg.showNumber(credit);
           break;
       case S4: 
           _shield.setLed(ParkingShield::RED_LED,false);
           _shield.setLed(ParkingShield::YELLOW_LED,false);
           _shield.setLed(ParkingShield::GREEN_LED,true);
           if(_shield.buttonS2Pressed()) parkingCountdown.setCredit(credit);
           _scheduler.scheduleTasks();
           credit=parkingCountdown.getNewCredit();
           _shield.sevenSeg.showNumber(credit);
           if(credit==1) Zustand=S5;
           break;
       case S5:
           _shield.setLed(ParkingShield::RED_LED,false);
           _shield.setLed(ParkingShield::YELLOW_LED,true);
           _shield.setLed(ParkingShield::GREEN_LED,false);
           _scheduler.scheduleTasks();
           credit=parkingCountdown.getNewCredit();
           _shield.sevenSeg.showNumber(credit);
           if(credit==0) Zustand=S1;
           
       
  }
}



