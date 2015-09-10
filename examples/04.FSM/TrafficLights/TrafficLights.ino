/**
 * @brief This sketch implements a traffic light controller.
 * @author Joern Hoffmann <jhoffmann@informatik.uni-leipzig.de>
 *
 * @description
 *  The sketch demonstrates the implementation of a finite state machine (FSM) with the Parking Shield. 
 *  The automata as has a seperate input, nextState and output method and is therefore classified as 3-FSM.
 *  Input:
 *    - button S1: advance to the next state
 *    - button S2: reset the FSM
 *   Output:
 *    - LED : the traffic lights (red, yellow and green)
 *    - 7 segment : shows the current state
 *    - decimal point: shows if the logic is sensitive to user control
 */

#include <ParkingShield.h>

/// The states of a traffic light
typedef enum : unsigned
{
  DISABLE,    // off
  STOP,       // red
  STOP_GO,    // red and yellow
  GO,         // green
  GO_STOP     // yellow
} state_t;


/// Bitmap to decide which LED should be enabled
typedef enum : unsigned
{
  RED     = 1 << 1,
  YELLOW  = 1 << 2,
  GREEN   = 1 << 3
} led_t;

bool tick;
state_t state = DISABLE;
ParkingShield shield;

void setup()
{ }

void loop()
{
  input();
  nextState();
  output();
}

/**
 * Enables an LED when its position in the bitmask is set.
 */
void showLeds(unsigned ledBitmask)
{
  shield.setLed(ParkingShield::RED_LED,     ledBitmask & RED);
  shield.setLed(ParkingShield::YELLOW_LED,  ledBitmask & YELLOW);
  shield.setLed(ParkingShield::GREEN_LED,   ledBitmask & GREEN);
}

/**
 * Samples the input.
 */
void input()
{
  // S1 pressed = allow the FSM to continue
  if (shield.buttonS1Pressed())
    tick = true;

  // S2 pressed = "asynchronously" reset the FSM
  if (shield.buttonS2Pressed())
    state = DISABLE;
}

/** 
 * Decides which state is next. 
 * @note Could be implemented much smaller, but it should show the general principle
 */
void nextState()
{
  switch (state)
  {
    case DISABLE:
      if (tick)
        state = STOP;
      break;

    case STOP:
      if (tick)
        state = STOP_GO;
      break;

    case STOP_GO:
      if (tick)
        state = GO;
      break;

    case GO:
      if (tick)
        state = GO_STOP;
      break;

    case GO_STOP:
      if (tick)
        state = STOP;
      break;
  }

  tick = false;
}

/**
 * @brief Sets the ouptput depending in the state..
 * @note The ouptut only depends on the internal state and not by transitions etc.
 * Therefore we have a Moore automata.
 */
void output()
{
  static unsigned ledBitmask = 0;
  
  switch (state)
  {
    case DISABLE:
      ledBitmask = 0;
      break;

    case STOP:
      ledBitmask = RED;
      break;

    case STOP_GO:
      ledBitmask = RED | YELLOW;
      break;

    case GO:
      ledBitmask = GREEN;
      break;

    case GO_STOP:
      ledBitmask = YELLOW;
      break;
  }

  showLeds(ledBitmask);
  shield.sevenSeg.showNumber(state);
}

