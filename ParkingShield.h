#ifndef PARKINGSHIELD_H
	#define PARKINGSHIELD_H

#include <SevenSeg.h>

/**
 * @brief The ParkingShield class is designed for the ParkingShield platform, an arduino extension board from J�rn Hoffmann at the University of Leipzig.
 * @brief It provides functionality to turn LEDs on/off, measure temperature and brightness, get button states.
 * @author Jörn Hoffmann (jhoffmann)
 * @author Marc Vester (XaserLE)
 */
class ParkingShield
{
	public:
	    typedef enum {
	      GREEN_LED,
	      YELLOW_LED,
	      RED_LED,
	      LED_MAX
	    } led_t;
	    
		/**
		 * @brief Constructor
		 */
		ParkingShield(void);

	    /**
	     * @brief Enables or disables an LED.
	     * @param led The led to set on or off.
	     * @param enable "True" enables and "false" disables the given led.
	     */
	    static void setLed(led_t led, bool enable);
 
		/**
		 * @brief Returns the actual measured temperature.
		 * @return Temperature as centigrade.
		 */
		unsigned int getTemperature(void) const;
	
		/**
		 * @brief Returns the actual measured brightness.
		 * @return Brightness.
		 */
		unsigned int getBrightness(void) const;
    
		/**
		 * @brief Returns whether button S1 is pressed or not.
		 * @return True if pressed, false otherwise.
		 */
		bool buttonS1Pressed(void) const;
		
		/**
		 * @brief Returns whether button S2 is pressed or not.
		 * @return True if pressed, false otherwise.
		 */
		bool buttonS2Pressed(void) const;
    
		/**
		 * @brief Use this to make sound with the buzzer.
		 * @param enable If true, buzzer makes noise. If false, buzzer is off.
		 */
		void setBuzzer(bool enable) const;
    
		/**
		 * @brief Show a number on the 7-segment display.
		 * @param number The number to be shown. Valid values: [0-9].
		 */
		SevenSeg const & sevenSeg(void) const { return _sevenSeg; }
  
	private:
		SevenSeg _sevenSeg;
};

#endif
