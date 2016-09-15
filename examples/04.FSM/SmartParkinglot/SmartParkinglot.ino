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

Channel<SoftwareSerial> channel(esp, scheduler, "AAAAAAAAAAAAAAAA", [](HttpRequest& request){
  request.addParameter("field1", String(shield.getTemperature()));
  request.addParameter("field2", String(shield.getBrightness()));
  request.addParameter("field3", String(parkinglot.getState()));
  request.addParameter("field4", String(parkinglot.getCredit()));
});

Talkback<SoftwareSerial> talkback(esp, 9999, "AAAAAAAAAAAAAAAA", [](String command){
  if(command == "pay") {
    parkinglot.process(Parkinglot::pay);
  } else if(command == "start") {
    parkinglot.process(Parkinglot::start);
    channel.scheduleUpload();
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
  // make background tasks visible (non-responsive ui)
  shield.sevenSeg.showDecimalPoint(true);
  scheduler.scheduleTasks();
  shield.sevenSeg.showDecimalPoint(false);

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
      channel.scheduleUpload();
    }
  }
  else
  {
    parkinglot.process(Parkinglot::free);
    channel.scheduleUpload();
  }
}
