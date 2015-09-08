#include <ParkingShield.h>
#include <DeviceArduino.h>
#include <Parkautomat.h>

static const int TIMEOUT_WARNING_THRESHOLD = 1;

bool Parkautomat::counterIsTimedOut()
{
    return shield.sevenSeg.number() == 0;
}

bool Parkautomat::shieldIsOccupied()
{
    return shield.getBrightness() < 900;
}

void Parkautomat::updateState(void)
{
    switch(state)
    {
    case OFF:
        updateStateOff();
        break;
    case UNPAYED:
        updateStateUnpayed();
        break;
    case PAYED:
        updateStatePayed();
        break;
    case PAYED_TIMEOUT_WARNING:
        updateStatePayedTimeoutWarning();
        break;
    }
}

void Parkautomat::ledsOff()
{
    shield.setLed(ParkingShield::GREEN_LED, false);
    shield.setLed(ParkingShield::YELLOW_LED, false);
    shield.setLed(ParkingShield::RED_LED, false);
}

void Parkautomat::updateStateOff()
{
    ledsOff();
    if( shieldIsOccupied() )
    {
        state = Parkautomat::UNPAYED;
    }
}

void Parkautomat::updateStateUnpayed()
{
    ledsOff();
    shield.setLed(ParkingShield::RED_LED, true);
    if( shield.buttonS1Pressed() )
    {
        state = Parkautomat::PAYED;
        shield.sevenSeg++;
    }
    if( !shieldIsOccupied() )
    {
        state = Parkautomat::OFF;
    }
}

void Parkautomat::updateStatePayed()
{
    ledsOff();
    shield.setLed(ParkingShield::GREEN_LED, true);
    if( shield.buttonS1Pressed() )
    {
        shield.sevenSeg++;
    }
    if( TIMEOUT_WARNING_THRESHOLD == shield.sevenSeg.number() )
    {
        state = Parkautomat::PAYED_TIMEOUT_WARNING;
    }
    if( !shieldIsOccupied() )
    {
        shield.sevenSeg.showNumber(0);
        state = Parkautomat::OFF;
    }
}

void Parkautomat::updateStatePayedTimeoutWarning()
{
    ledsOff();
    shield.setLed(ParkingShield::YELLOW_LED, true);
    if( shield.buttonS1Pressed() )
    {
        shield.sevenSeg++;
    }
    if( TIMEOUT_WARNING_THRESHOLD < shield.sevenSeg.number() )
    {
        state = Parkautomat::PAYED;
    }
    if( counterIsTimedOut() )
    {
        shield.sevenSeg.showNumber(0);
        state = Parkautomat::UNPAYED;
    }
    if( !shieldIsOccupied() )
    {
        shield.sevenSeg.showNumber(0);
        state = Parkautomat::OFF;
    }
}



