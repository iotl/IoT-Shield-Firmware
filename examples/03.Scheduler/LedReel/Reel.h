#ifndef REEL_H
#define REEL_H

#include <ParkingShield.h>
#include <Task.h>

class Reel : public Task
{
  public:
    enum Direction {left, right};

    Reel(ParkingShield &shield, Direction direction = left) : shield(shield), direction(direction)
    {
      shield.sevenSeg.clear();
    }

    void update(void)
    {
      switch(direction)
      {
        case right:
          shield.sevenSeg.showSegment(segments[counter], inverted);
          if((counter-1)<0) shield.sevenSeg.showSegment(SevenSeg::SEGMENT_F, !inverted);
          else shield.sevenSeg.showSegment(segments[counter-1], !inverted);
          counter=(counter+1)%6;
          break;

        case left:
          shield.sevenSeg.showSegment(segments[counter], !inverted);
          if((counter-1)<0) shield.sevenSeg.showSegment(SevenSeg::SEGMENT_F, inverted);
          else shield.sevenSeg.showSegment(segments[counter-1], inverted);
          counter=(counter+5)%6;
          break;
      }
    }

    void switchDirection(Direction direction)
    {
      this->direction = direction;
    }

  private:
    ParkingShield& shield;
    Direction direction;

    int counter = 0;
    bool inverted = false;

    SevenSeg::segment_t segments[6] = {
      SevenSeg::SEGMENT_A,
      SevenSeg::SEGMENT_B,
      SevenSeg::SEGMENT_C,
      SevenSeg::SEGMENT_D,
      SevenSeg::SEGMENT_E,
      SevenSeg::SEGMENT_F
    };
};

#endif
