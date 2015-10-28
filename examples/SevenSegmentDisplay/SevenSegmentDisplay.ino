#include <ParkingShield.h>

ParkingShield shield;
int counter = 0;

void setup()
{
  shield.setRepeatInterval(250);
}

void loop(void)
{
  if (shield.buttonS1Pressed())
      counter = ++counter % SevenSeg::NUMBER_SYMBOLS;

  shield.sevenSeg.showSymbol(static_cast<SevenSeg::symbol_t>(counter));
}

