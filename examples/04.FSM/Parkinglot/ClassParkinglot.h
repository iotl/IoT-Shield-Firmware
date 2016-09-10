#ifndef ClassParkinglot_H
#define ClassParkinglot_H

#include <Task.h>
#include <Scheduler.h>
#include "Countdown.h"

class ClassParkinglot
{
  //----------------------------------
  public:
  
    enum Alphabet {ready, free, pay, start, tick, alert};//EingabeAlphabet
    typedef Alphabet Alphabet; 
    int credit;

    //ClassParkinglot(ParkingShield &shield, Scheduler &scheduler )
    ClassParkinglot(ParkingShield &shield)
    {
        this->Zustand = S0;                              //Startzustand
        this->_shield = shield;
        this->credit = 0;
        
        _scheduler.addTask(&parkingCountdown, 1000, true);
    }

    void Prozess(Alphabet Ereignis);
    
  //----------------------------------
  private:

    enum Zustandsmenge {S0,S1,S2,S3,S4,S5};
    typedef Zustandsmenge Zustandsmenge;                //endliche Zustandsmenge

    Zustandsmenge Zustand;
    ParkingShield _shield;
    Scheduler _scheduler;
    Countdown parkingCountdown;

    Zustandsmenge Ueberfuehrungsfunktion[6][6] =        //Zustandsüberführungsfunktion
//  ready, free, pay, start, tick, alert  
    {{S1,  S0,   S0,  S0,    S0,   S0}, //S0
    { S1,  S0,   S2,  S1,    S1,   S1}, //S1
    { S2,  S0,   S3,  S5,    S2,   S2}, //S2
    { S3,  S0,   S3,  S4,    S3,   S3}, //S3
    { S4,  S0,   S3,  S4,    S4,   S5}, //S4
    { S5,  S0,   S2,  S5,    S1,   S5}};//S5

};

//----------------------------------



#endif
