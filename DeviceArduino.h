#ifndef DEVICE_H
  #define DEVICE_H

#include <stdint.h>

/**
 * @brief The Device class abstracts hardware specific stuff from the Arduino.
 * @brief This was a proof of concept and there are missing some things like Serial.xxx.
 * @brief All classes that belong to the ParkingShield are using this abstraction layer.
 * @brief Therefore it is possible to separate the ParkingShield and use a completely
 * @brief different device (or an emulator).
 * @author Marc Vester (XaserLE)
 */
class Device
{
  	public:
  		typedef enum
  		{
  			SIGNAL_LOW,
  			SIGNAL_HIGH,
  			NUMBER_SIGNALS
  		} signal_t;

  		typedef enum
  		{
  			PINMODE_OUTPUT,
  			PINMODE_INPUT,
  			PINMODE_INPUT_PULLUP,
  			NUMBER_PINMODES
  		} pinmode_t;

	  	typedef enum
	  	{
	  		DIGITAL_PIN_0,
	  		DIGITAL_PIN_1,
	  		DIGITAL_PIN_2,
	  		DIGITAL_PIN_3,
	  		DIGITAL_PIN_4,
	  		DIGITAL_PIN_5,
	  		DIGITAL_PIN_6,
	  		DIGITAL_PIN_7,
	  		DIGITAL_PIN_8,
	  		DIGITAL_PIN_9,
	  		DIGITAL_PIN_10,
	  		DIGITAL_PIN_11,
	  		DIGITAL_PIN_12,
	  		DIGITAL_PIN_13,
	  		ANALOG_PIN_0,
	  		ANALOG_PIN_1,
	  		ANALOG_PIN_2,
	  		ANALOG_PIN_3,
	  		ANALOG_PIN_4,
	  		ANALOG_PIN_5,
	  		NUMBER_PINS
	  	} pin_t;

	    static void setPinMode(pin_t pin, pinmode_t pinmode);
	    static unsigned int analogReadPin(pin_t pin);
	    static void analogWritePin(pin_t pin, uint8_t value);
	    static signal_t digitalReadPin(pin_t pin);
	    static void digitalWritePin(pin_t pin, signal_t signal);
	    static unsigned long int milliseconds(void);
    	static void delayMillis(unsigned long milliseconds);
    	static void delayMicros(unsigned int microseconds);
    	
    private:
    	static bool isPinValid(pin_t pin);
    	static bool isPinmodeValid(pinmode_t pinmode);
    	static bool isSignalValid(signal_t signal);
};

#endif // DEVICE_H
