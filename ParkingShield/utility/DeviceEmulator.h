#ifndef DEVICE_H
  #define DEVICE_H

#include <Arduino.h>

class Device
{
  public:
    static void setPinMode(uint8_t pin, uint8_t mode) { Serial.println("Pin " + String(pin) + " auf mode " + String(mode) + " gesetzt"); }
    static unsigned int analogReadPin(uint8_t pin) { Serial.println("Pin " + String(pin) + " analog gelesen"); return pin; }
    static void analogWritePin(uint8_t pin, uint8_t value) { Serial.println("Pin " + String(pin) + " mit " + String(value) + " analog beschrieben"); }
    static unsigned int digitalReadPin(uint8_t pin) { Serial.println("Pin " + String(pin) + " digital gelesen"); return pin; }
    static void digitalWritePin(uint8_t pin, uint8_t value) { Serial.println("Pin " + String(pin) + " mit " + String(value) + " analog beschrieben"); }
};

#endif // DEVICE_H
