#ifndef DEVICE_H
  #define DEVICE_H

#include <Arduino.h>

class Device
{
  public:
    static void setPinMode(uint8_t pin, uint8_t mode) { pinMode(pin, mode); }
    static unsigned int analogReadPin(uint8_t pin) { analogRead(pin); }
    static void analogWritePin(uint8_t pin, uint8_t value) { analogWrite(pin, value); }
    static unsigned int digitalReadPin(uint8_t pin) { return digitalRead(pin); }
    static void digitalWritePin(uint8_t pin, uint8_t value) { digitalWrite(pin, value); }
};

#endif // DEVICE_H
