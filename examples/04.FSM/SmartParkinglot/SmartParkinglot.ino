#include <SoftwareSerial.h>
#include <ParkingShield.h>
#include <Scheduler.h>

#include "Parkinglot.h"
#include "Thingspeak.h"

Scheduler scheduler;

ParkingShield shield;
Parkinglot parkinglot(shield);

SoftwareSerial espSerial(2, 3);
Esp8266<SoftwareSerial> esp(espSerial);

Talkback<SoftwareSerial> talkback(esp, 9999, "AAAAAAAAAAAAAAAA", [](String command){
  if(command == "pay") {
    parkinglot.process(Parkinglot::pay);
  } else if(command == "start") {
    parkinglot.process(Parkinglot::start);
  }
});


void setup(void)
{
  Serial.begin(9600);

  setupWlan(esp, "eduinfo", "");

  shield.setRepeatInterval(250);
  scheduler.addTask(&parkinglot, 4000, true);
  scheduler.addTask(&talkback, 5000, true);
}

void loop(void)
{
  scheduler.scheduleTasks();
  if(shield.getBrightness() < 700)
  {
    parkinglot.process(Parkinglot::ready);
    if(shield.buttonS1Pressed())
    {
      parkinglot.process(Parkinglot::pay);
    }
    else if(shield.buttonS2Pressed())
    {
      parkinglot.process(Parkinglot::start);
    }
  }
  else
  {
    parkinglot.process(Parkinglot::free);
  }
}

