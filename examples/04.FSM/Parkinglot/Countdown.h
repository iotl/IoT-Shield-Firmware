#ifndef Countdown_h
#define Countdown_h

#include <Task.h>
#include <Scheduler.h>
#include "ClassParkinglot.h"


class Countdown : public Task
{
  public:
    Countdown()
    {
      credit=0;
    }
    //Countdown(ParkingShield &shield, ClassParkinglot &parkinglot) : shield(shield),parkinglot(parkinglot)


    void update(void)
    {
      if(credit>=1)
      credit--;
    }

    int getNewCredit()
    {
      return credit;
    }

    void setCredit(int _credit)
    {
      credit=_credit;
    }


  private:
  
    int credit;
};


#endif
