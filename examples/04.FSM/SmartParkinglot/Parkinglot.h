#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <Task.h>

class ParkingShield;

class Parkinglot : public Task
{
  public:
    enum Events {ready, free, pay, start, tick}; //Eingabealphabet
    enum States {S0,S1,S2,S3,S4,S5};

    Parkinglot(ParkingShield &shield) : shield(shield) {}

    void update(void);
    void process(Events event);

    States getState();
    unsigned int getCredit();

  private:
    States state = S0;
    ParkingShield &shield;
    unsigned int credit;

    States transitions[6][5] =
//    ready, free, pay, start, tick
      {{S1,  S0,   S0,  S0,    S0}, //S0
      { S1,  S0,   S2,  S1,    S1}, //S1
      { S2,  S0,   S3,  S5,    S2}, //S2
      { S3,  S0,   S3,  S4,    S3}, //S3
      { S4,  S0,   S3,  S4,    S4}, //S4
      { S5,  S0,   S3,  S5,    S1}};//S5

    void setLeds(bool red, bool yellow, bool green);
};

#endif
