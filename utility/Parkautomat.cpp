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

void Parkautomat::enterStateOff()
{
    state = OFF;
    ledsOff();
}

void Parkautomat::updateStateOff()
{
    if( shieldIsOccupied() )
    {
        enterStateUnpayed();
    }
}

void Parkautomat::enterStateUnpayed()
{
    state = UNPAYED;
    ledsOff();
    shield.setLed(ParkingShield::RED_LED, true);
}

void Parkautomat::updateStateUnpayed()
{
    if( shield.buttonS1Pressed() )
    {
        enterStatePayed();
        shield.sevenSeg++;
    }
    if( !shieldIsOccupied() )
    {
        enterStateOff();
    }
}

void Parkautomat::enterStatePayed()
{
    state = PAYED;
    ledsOff();
    shield.setLed(ParkingShield::GREEN_LED, true);
}

void Parkautomat::updateStatePayed()
{
    if( shield.buttonS1Pressed() )
    {
        shield.sevenSeg++;
    }
    if( TIMEOUT_WARNING_THRESHOLD == shield.sevenSeg.number() )
    {
        enterStatePayedTimeoutWarning();
    }
    if( !shieldIsOccupied() )
    {
        shield.sevenSeg.showNumber(0);
        enterStateOff();
    }
}

void Parkautomat::enterStatePayedTimeoutWarning()
{
    state = PAYED_TIMEOUT_WARNING;
    ledsOff();
    shield.setLed(ParkingShield::YELLOW_LED, true);
}

void Parkautomat::updateStatePayedTimeoutWarning()
{
    if( shield.buttonS1Pressed() )
    {
        shield.sevenSeg++;
    }
    if( TIMEOUT_WARNING_THRESHOLD < shield.sevenSeg.number() )
    {
        enterStatePayed();
    }
    if( counterIsTimedOut() )
    {
        shield.sevenSeg.showNumber(0);
        enterStateUnpayed();
    }
    if( !shieldIsOccupied() )
    {
        shield.sevenSeg.showNumber(0);
        enterStateOff();
    }
}



