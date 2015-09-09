#ifndef PARKAUTOMAT_H
  #define PARKAUTOMAT_H


class Parkautomat
{
  public:
      Parkautomat(ParkingShield &shield) : _shield(shield), state(OFF) {}
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
  
      ParkingShield & _shield;
      State state;
};

#endif //PARKAUTOMAT_H
