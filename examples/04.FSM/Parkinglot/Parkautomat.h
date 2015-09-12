#ifndef PARKAUTOMAT_H
  #define PARKAUTOMAT_H

#include <Task.h>
#include <Scheduler.h>

class Countdown : public Task
{
  public:
    Countdown(ParkingShield & shield) : shield(shield) {}
    
    void update(void);
    
  private:
    ParkingShield & shield;
};

class Parkautomat
{
  public:
      Parkautomat(ParkingShield &shield, Scheduler & scheduler) : countdown(shield), _shield(shield), _scheduler(scheduler), state(OFF) {}
      void update(void);
      
  private:
      void ledsOff();
      bool shieldIsOccupied();
      bool counterIsTimedOut();
      void enterStateOff();
      void enterStateUnpayed();
      void enterStatePayed();
      void enterStatePayedTimeoutWarning();
      void updateStateOff();
      void updateStateUnpayed();
      void updateStatePayed();
      void updateStatePayedTimeoutWarning();
  
      typedef enum
      {
          OFF,
          UNPAYED,
          PAYED,
          PAYED_TIMEOUT_WARNING
      } State;

      Countdown countdown;
      ParkingShield & _shield;
      Scheduler & _scheduler;
      State state;
};

#endif //PARKAUTOMAT_H
