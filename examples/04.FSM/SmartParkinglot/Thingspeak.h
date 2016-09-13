#ifndef THINGSPEAK_H
#define THINGSPEAK_H

#include <Task.h>
#include <SoftwareSerial.h>
#include <IPDParser.h>
#include <HttpRequest.h>
#include <Esp8266.h>

#include "Parkinglot.h"

void setupWlan(Esp8266<SoftwareSerial>& esp, const char* ssid, const char* psk);

class Talkback : public Task {
  public:
    Talkback(SoftwareSerial& serial, Esp8266<SoftwareSerial>& esp, Parkinglot& parkinglot, unsigned int apiId, const char* apiKey);

    void update();

  private:
    SoftwareSerial& serial;
    Esp8266<SoftwareSerial>& esp;
    Parkinglot& parkinglot;
    unsigned int apiId;
    const char* apiKey;
};

#endif
