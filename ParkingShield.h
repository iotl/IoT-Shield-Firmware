#ifndef PARKINGSHIELD_H
	#define PARKINGSHIELD_H

#include <SevenSeg.h>
#include <stdint.h>

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
		 * @brief Let's the buzzer make sound.
		 * @param frequenzyInHertz The frequenz in hertz.
		 * @param timeInMilliseconds The duration of the sound in milliseconds.
		 */
		void beep(int frequencyInHertz, long timeInMilliseconds) const;

		/**
		 * @brief Play's a tone.
		 * @param tone The tone to play.
		 * @param duration The duration in microseconds.
		 */
		void playTone(int tone, int duration) const;

		/**
		 * @brief Play's a note.
		 * @param note The note to play.
		 * @param duration The duration in microseconds.
		 */
		void playNote(char note, int duration) const;

		/**
		 *@brief Play's a popular melody :-D
		 */
		void playMelody(void) const;

		/**
		 * @brief Play's the storm trooper march :-D
		 * @brief Much thanks to tagliati (https://gist.github.com/tagliati/1804108).
		 */
		void playMarch(bool shortVersion = true) const;

		/**
		 * @brief Asynchronous decrements the number on the seven segment display by 1 every second.
		 */
		void countdown(void);

		/// The seven segment display, accessable from outside.
		SevenSeg sevenSeg;

	private:
		bool _countDown;
};

#endif
