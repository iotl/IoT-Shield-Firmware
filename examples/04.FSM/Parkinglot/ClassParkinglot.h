#ifndef ClassParkinglot_H
#define ClassParkinglot_H

#include <Task.h>

class ClassParkinglot : public Task
{
  public:
    enum Events {ready, free, pay, start, tick}; //Eingabealphabet
    enum States {S0,S1,S2,S3,S4,S5};

    ClassParkinglot(ParkingShield &shield) : shield(shield) {}

    void update(void);
    void process(Events event);

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
      { S5,  S0,   S2,  S5,    S1}};//S5

    void setLeds(bool red, bool yellow, bool green);
};

#endif
