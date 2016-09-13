#include <ParkingShield.h>
#include "Parkinglot.h"

void Parkinglot::setLeds(bool red, bool yellow, bool green)
{
  shield.setLed(ParkingShield::RED_LED, red);
  shield.setLed(ParkingShield::YELLOW_LED, yellow);
  shield.setLed(ParkingShield::GREEN_LED, green);
}

void Parkinglot::update(void)
{
  process(tick);
}

void Parkinglot::process(Events event)
{
  // input
  if(event == pay && credit <9) {
    credit++;
  }
  if(event == free) {
    credit = 0;
  }
  if(event == tick && (state == S4 || state == S5) && credit >= 1) {
    credit--;
  }

  // transition
  if(event == tick && state == S4 && credit == 1) {
    // special tick if only one credit left: enter alert state (S5)
    state = S5;
  } else {
    state = transitions[state][event];
  }

  // output
  switch(state)
  {
    case S0:
      setLeds(false, false, false);
      shield.sevenSeg.clear();
      break;
    case S1:
      setLeds(true, false, false);
      shield.sevenSeg.showNumber(credit);
      break;
    case S2:
      setLeds(true, false, false);
      shield.sevenSeg.showNumber(credit);
      break;
    case S3:
      setLeds(true, false, false);
      shield.sevenSeg.showNumber(credit);
      break;
    case S4:
      setLeds(false, false, true);
      shield.sevenSeg.showNumber(credit);
      break;
    case S5:
      setLeds(false, true, false);
      shield.sevenSeg.showNumber(credit);
      break;
  }
}

