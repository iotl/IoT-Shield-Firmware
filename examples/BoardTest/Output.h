#ifndef OUTPUT_H
  #define OUTPUT_H

#include <Task.h>
#include <Scheduler.h>
#include <ParkingShield.h>
#include <Arduino.h>

class Output : public Task
{
  public:
    Output(ParkingShield & shield) : _shield(shield) {}
    virtual ~Output() {}
    
    virtual void update(Scheduler * scheduler)
    {
      Serial.print("Button S1: ");
      Serial.println(_shield.buttonS1Pressed());
      Serial.print("Button S2: ");
      Serial.println(_shield.buttonS2Pressed());
      Serial.print("Licht: ");
      Serial.println(_shield.getBrightness());
      Serial.print("Temperatur: ");
      Serial.print(_shield.getTemperature());
      Serial.println(" Grad Celsius");
    }
    
  private:
    ParkingShield & _shield;
};

#endif OUTPUT_H
