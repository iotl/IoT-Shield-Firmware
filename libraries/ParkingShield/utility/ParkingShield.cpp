#include <ParkingShield.h>
//#include <DeviceEmulator.h>
#include <DeviceArduino.h>


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

typedef enum {
  BUTTON_S1,
  BUTTON_S2,
  BRIGHTNESS,  
  TEMPERATURE,  
  INPUT_MAX
} input_t;

typedef enum {
  LED_GREEN = ParkingShield::GREEN_LED,
  LED_YELLOW = ParkingShield::YELLOW_LED,
  LED_RED = ParkingShield::RED_LED,
  BUZZER,
  OUTPUT_MAX
} output_t;

unsigned int output_pins[OUTPUT_MAX] = {4, A5, A4, 5};
unsigned int input_pins[INPUT_MAX] = {A0, A1, A2, A3};

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

void setPinMode(unsigned int pin, uint8_t mode)
{
  Device::setPinMode(pin, mode);
}

void setupOutput()
{
  for (unsigned int output = 0; output < OUTPUT_MAX; output++)
    setPinMode(output_pins[output], OUTPUT);
}

void setupInput()
{
  for (unsigned int input = 0; input < INPUT_MAX; input++)
    setPinMode(input_pins[input], INPUT);
}

unsigned int analogReadPin(input_t inputPin)
{
  if (!isInputPinValid(inputPin))
    return 0;

  return Device::analogReadPin(input_pins[inputPin]); 
}

void analogWritePin(output_t outputPin, uint8_t value)
{
  if (isOutputPinValid(outputPin))
    Device::analogWritePin(output_pins[outputPin], value);
}

unsigned int digitalReadPin(input_t inputPin)
{
  if (!isInputPinValid(inputPin))
    return 0;

  return Device::digitalReadPin(input_pins[inputPin]);
}

void digitalWritePin(output_t outputPin, uint8_t value)
{
  if (isOutputPinValid(outputPin))
    Device::digitalWritePin(output_pins[outputPin], value);
}

void ParkingShield::setLed(led_t led, bool enable)
{
  if (isLedValid(led))
    digitalWritePin(static_cast<output_t>(led), enable ? LOW : HIGH);
}

void setAllLeds(bool enable)
{
  for (unsigned int led = 0; led < ParkingShield::LED_MAX; led++)
    ParkingShield::setLed(static_cast<ParkingShield::led_t>(led), enable);
}

// ---------------------------------------------------------------------------------------------------- //
// Public
// ---------------------------------------------------------------------------------------------------- //
ParkingShield::ParkingShield(void) : sevSeg(7,8,9,10,11,12,13,6)
{
  setupOutput();
  setupInput();
  
  setAllLeds(false);
}

bool ParkingShield::buttonS1Pressed(void)
{
	if (digitalReadPin(BUTTON_S1) == HIGH)
		return true;
  else
    return false;
}

bool ParkingShield::buttonS2Pressed(void)
{
  if (digitalReadPin(BUTTON_S2) == HIGH)
    return true;
  else
		return false;
}

unsigned int ParkingShield::getTemperature(void) const
{ 
  unsigned int tempVoltage = analogReadPin(TEMPERATURE);
  return (tempVoltage / 1024.0) * 5.0 * 100.0; 
}

unsigned int ParkingShield::getBrightness(void) const
{
  return analogReadPin(BRIGHTNESS);
}


void ParkingShield::setBuzzer(uint8_t value)
{
	digitalWritePin(BUZZER, value);
}
