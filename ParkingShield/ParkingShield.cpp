#include "ParkingShield.h"
//#include <DeviceEmulator.h>
#include "utility/DeviceArduino.h"


// ---------------------------------------------------------------------------------------------------- //
// Helper 
// ---------------------------------------------------------------------------------------------------- //
/*
typedef union{    
  struct {
    unsigned int red,
    unsigned int yellow,
    unsigned int green,
  };
  
  unsigned int leds[LED_MAX]; 
} led_translation;

static led_translation leds = {.red=a4, .yellow=a5, .green=4};
*/

typedef enum
{
  BUTTON_S1,
  BUTTON_S2,
  BRIGHTNESS,  
  TEMPERATURE,  
  INPUT_MAX
} input_t;

typedef enum
{
  LED_GREEN = ParkingShield::GREEN_LED,
  LED_YELLOW = ParkingShield::YELLOW_LED,
  LED_RED = ParkingShield::RED_LED,
  BUZZER,
  OUTPUT_MAX
} output_t;

Device::pin_t output_pins[OUTPUT_MAX] = {Device::DIGITAL_PIN_4, Device::ANALOG_PIN_5, Device::ANALOG_PIN_4, Device::DIGITAL_PIN_5};
Device::pin_t input_pins[INPUT_MAX] = {Device::ANALOG_PIN_0, Device::ANALOG_PIN_1, Device::ANALOG_PIN_2, Device::ANALOG_PIN_3};
Device::pin_t sevensegment_pins[8] = {Device::DIGITAL_PIN_7,Device::DIGITAL_PIN_8,Device::DIGITAL_PIN_9,Device::DIGITAL_PIN_10,Device::DIGITAL_PIN_11,Device::DIGITAL_PIN_12,Device::DIGITAL_PIN_13,Device::DIGITAL_PIN_6};

bool isInputPinValid(input_t inputPin)
{
  return inputPin < INPUT_MAX;
}

bool isOutputPinValid(output_t outputPin)
{
  return outputPin < OUTPUT_MAX;
}

bool isLedValid(ParkingShield::led_t led)
{
  return led < ParkingShield::LED_MAX;
}

void setPinMode(Device::pin_t pin, Device::pinmode_t pinmode)
{
  Device::setPinMode(pin, pinmode);
}

void setupOutput()
{
  for (unsigned int output = 0; output < OUTPUT_MAX; output++)
    setPinMode(output_pins[output], Device::PINMODE_OUTPUT);
}

void setupInput()
{
  for (unsigned int input = 0; input < INPUT_MAX; input++)
    setPinMode(input_pins[input], Device::PINMODE_INPUT);
}

unsigned int analogReadPin(input_t inputPin)
{
  if (isInputPinValid(inputPin))
    return Device::analogReadPin(input_pins[inputPin]); 

  return 0;
}

void analogWritePin(output_t outputPin, uint8_t value)
{
  if (isOutputPinValid(outputPin))
    Device::analogWritePin(output_pins[outputPin], value);
}

Device::signal_t digitalReadPin(input_t inputPin)
{
  if (isInputPinValid(inputPin))
    return Device::digitalReadPin(input_pins[inputPin]);

  return Device::SIGNAL_LOW;
}

void digitalWritePin(output_t outputPin, Device::signal_t signal)
{
  if (isOutputPinValid(outputPin))
    Device::digitalWritePin(output_pins[outputPin], signal);
}

void ParkingShield::setLed(led_t led, bool enable)
{
  if (isLedValid(led))
    digitalWritePin(static_cast<output_t>(led), enable ? Device::SIGNAL_LOW : Device::SIGNAL_HIGH);
}

void setAllLeds(bool enable)
{
  for (unsigned int led = 0; led < ParkingShield::LED_MAX; led++)
    ParkingShield::setLed(static_cast<ParkingShield::led_t>(led), enable);
}

// ---------------------------------------------------------------------------------------------------- //
// Public
// ---------------------------------------------------------------------------------------------------- //
ParkingShield::ParkingShield(void)  : sevSeg(sevensegment_pins, false, true)
{
  setupOutput();
  setupInput();
  
  setAllLeds(false);
}

bool ParkingShield::buttonS1Pressed(void) const
{
	if (digitalReadPin(BUTTON_S1) == Device::SIGNAL_HIGH)
		return true;
  else
    return false;
}

bool ParkingShield::buttonS2Pressed(void) const
{
  if (digitalReadPin(BUTTON_S2) == Device::SIGNAL_HIGH)
    return true;
  else
		return false;
}

unsigned int ParkingShield::getTemperature(void) const
{ 
  unsigned int tempVoltage = analogReadPin(TEMPERATURE);
  return (tempVoltage / 1024.0) * 5.0 * 100.0 - 5.0; 
}

unsigned int ParkingShield::getBrightness(void) const
{
  return analogReadPin(BRIGHTNESS);
}


void ParkingShield::setBuzzer(bool enable) const
{
	digitalWritePin(BUZZER, enable ? Device::SIGNAL_HIGH : Device::SIGNAL_LOW);
}

void ParkingShield::setDecimalPoint(bool enable) const
{
  sevSeg.setDecimalPoint(enable);
}