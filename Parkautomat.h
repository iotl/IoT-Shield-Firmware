#ifndef PARKAUTOMAT_H
#define PARKAUTOMAT_H


class Parkautomat
{

public:
    Parkautomat(ParkingShield &shield) : shield(shield) {}
    void updateState(void);
private:
    void ledsOff();
    bool shieldIsOccupied();
    bool counterIsTimedOut();
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

    ParkingShield shield;
    State state;
};

#endif //PARKAUTOMAT_H
