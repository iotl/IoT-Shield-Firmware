#ifndef SEVENSEG_H
	#define SEVENSEG_H

#include <Arduino.h>

#define SEGMENT_LED_OFF HIGH
#define SEGMENT_LED_ON LOW

/**
 * @brief The SevenSeg class provides functionality to show the digits [0-9] and the decimal point on a single 7-segment display.
 * @author Lukas Fischer
 * @author Marc Vester (XaserLE)
 */
class SevenSeg
{
	public:
		/**
		 * @brief Constructor
		 * @brief The letters are ordered as follows: a = top, b = upper right, c = lower right, d = bottom, e = lower left, f = upper left, g = middle.
		 * @param pin_a The arduino pin that is connected to segment a.
		 * @param pin_b The arduino pin that is connected to segment b.
		 * @param pin_c The arduino pin that is connected to segment c.
		 * @param pin_d The arduino pin that is connected to segment d.
		 * @param pin_e The arduino pin that is connected to segment e.
		 * @param pin_f The arduino pin that is connected to segment f.
		 * @param pin_g The arduino pin that is connected to segment g.
		 * @param pin_dp The arduino pin that is connected to the segment with the decimal point.
		 */
		SevenSeg(int pin_a, int pin_b, int pin_c, int pin_d, int pin_e, int pin_f, int pin_g, int pin_dp);
	
		/**
		 * @brief Destructor
		 */
		~SevenSeg() {}
    
		/**
		 * @brief Shows a number on the display.
		 * @param num The number to show. Valid values: [0-9]. If num is invalid, the display will show a "-".
		 */
		void setNumber(int num);
	
		/**
		 * @brief Turns the decimal point on.
		 */
		void decimalPointOn(void) { digitalWrite(pin_dp, SEGMENT_LED_ON); }
		
		/**
		 * @brief Turns the decimal point off.
		 */
		void decimalPointOff(void) { digitalWrite(pin_dp, SEGMENT_LED_OFF); }
  
	private:
		static const int NUM_SEGMENTS = 7;
		int segmentPins[NUM_SEGMENTS] = {0};
		static const int segmentsForNumbers[11][NUM_SEGMENTS];
		int pin_dp;
};

#endif
