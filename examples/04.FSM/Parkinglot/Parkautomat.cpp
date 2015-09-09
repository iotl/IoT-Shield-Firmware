#include <ParkingShield.h>
#include <Task.h>
#include "Parkautomat.h"

void Countdown::update(Scheduler & scheduler)
{
    char number = shield.sevenSeg.number();
    
    if (number < 1)
        return;

    shield.sevenSeg.showNumber(number-1);
}


static const int TIMEOUT_WARNING_THRESHOLD = 1;

bool Parkautomat::counterIsTimedOut()
{
    return _shield.sevenSeg.number() == 0;
}

bool Parkautomat::shieldIsOccupied()
{
    return _shield.getAverageBrightness() <= 1000;
}

void Parkautomat::update(void)
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
        default:
            break;
    }
}

void Parkautomat::ledsOff()
{
    _shield.setLed(ParkingShield::GREEN_LED, false);
    _shield.setLed(ParkingShield::YELLOW_LED, false);
    _shield.setLed(ParkingShield::RED_LED, false);
}

void Parkautomat::enterStateOff()
{
    state = OFF;
    ledsOff();
    _shield.sevenSeg.clear();
    _scheduler.removeTask(&countdown);
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
    _shield.sevenSeg.showNumber(0);
    _shield.setLed(ParkingShield::RED_LED, true);
    _scheduler.removeTask(&countdown);
}

void Parkautomat::updateStateUnpayed()
{
    if( _shield.buttonS1Pressed() )
    {
        enterStatePayed();
        _shield.sevenSeg.showNumber( 1 + TIMEOUT_WARNING_THRESHOLD);
        _scheduler.addTask(&countdown, 2000);
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
    _shield.setLed(ParkingShield::GREEN_LED, true);
}

void Parkautomat::updateStatePayed()
{
    if( _shield.buttonS1Pressed() )
        _shield.sevenSeg++;
        
    if( TIMEOUT_WARNING_THRESHOLD == _shield.sevenSeg.number() )
    {
        enterStatePayedTimeoutWarning();
    }
    
    if( !shieldIsOccupied() )
    {
        _shield.sevenSeg.clear();
        enterStateOff();
    }
}

void Parkautomat::enterStatePayedTimeoutWarning()
{
    state = PAYED_TIMEOUT_WARNING;
    ledsOff();
    _shield.setLed(ParkingShield::YELLOW_LED, true);
}

void Parkautomat::updateStatePayedTimeoutWarning()
{
    if( _shield.buttonS1Pressed() )
    {
        _shield.sevenSeg++;
    }
    
    if( TIMEOUT_WARNING_THRESHOLD < _shield.sevenSeg.number() )
    {
        enterStatePayed();
    }
    
    if( counterIsTimedOut() )
    {
        enterStateUnpayed();
    }
    
    if( !shieldIsOccupied() )
    {
        enterStateOff();
    }
}


