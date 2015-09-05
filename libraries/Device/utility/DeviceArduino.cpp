#include <DeviceArduino.h>


uint8_t pinMap[Device::NUMBER_PINS] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5 };
uint8_t signalMap[Device::NUMBER_SIGNALS] = { LOW, HIGH };
uint8_t pinmodeMap[Device::NUMBER_PINMODES] = { OUTPUT, INPUT, INPUT_PULLUP };

void Device::setPinMode(pin_t pin, pinmode_t pinmode)
{
    if (isPinValid(pin) && isPinmodeValid(pinmode))
        pinMode(pinMap[pin], pinmodeMap[pinmode]);
}

unsigned int Device::analogReadPin(pin_t pin)
{
    if (isPinValid(pin))
        return analogRead(pinMap[pin]);

    return 0;
}

void Device::analogWritePin(pin_t pin, uint8_t value)
{
    if (isPinValid(pin))
        analogWrite(pinMap[pin], value);
}

Device::signal_t Device::digitalReadPin(pin_t pin)
{
    if (isPinValid(pin))
        return digitalRead(pinMap[pin]) == HIGH ? Device::SIGNAL_HIGH : Device::SIGNAL_LOW;

    return Device::SIGNAL_LOW;
}

void Device::digitalWritePin(pin_t pin, signal_t signal)
{
    if (isPinValid(pin) && isSignalValid(signal))
    {
        digitalWrite(pinMap[pin], signalMap[signal]);
    }
}

bool Device::isPinValid(pin_t pin)
{
    return pin < NUMBER_PINS;
}

bool Device::isPinmodeValid(pinmode_t pinmode)
{
    return pinmode < NUMBER_PINMODES;
}

bool Device::isSignalValid(signal_t signal)
{
    return signal < NUMBER_SIGNALS;
}
