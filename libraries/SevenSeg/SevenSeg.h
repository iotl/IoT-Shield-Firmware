#ifndef SEVENSEG_H
	#define SEVENSEG_H

#include <DeviceArduino.h>
//#include <DeviceEmulator.h>
#include <stdint.h>


/**
 * @brief The SevenSeg class provides functionality to show the digits [0-9] and the decimal point on a single 7-segment display.
 * @author Marc Vester (XaserLE)
 * @author Lukas Fischer
 */
class SevenSeg
{
	public:
		/**
		 * @brief Constructor
		 * @brief		 ---a---
		 * @brief		|		|
		 * @brief		|f		|b
		 * @brief		|		|
		 * @brief		 ---g---
		 * @brief		|		|
		 * @brief		|e		|c
		 * @brief		|		|
		 * @brief		 ---d---	dp
		 * @param segmentPins An array with the device pins that are connected to the 7-seg display, starting with 'a' and ending with 'g'. See above for order. Length: [7-8], dependent on the decimal point.
		 * @param anode Indicates whether the 7-seg display is common anode (true) or common cathode (false).
		 * @param hasDecimalPoint Indicates whether the 7-seg display has a decimal point or not.
		 * @param
		 */
		SevenSeg(Device::pin_t segmentPins[], bool anode, bool hasDecimalPoint = false);
    
		/**
		 * @brief Shows a number on the display.
		 * @param num The number to show. Valid values: [0-9]. If num is invalid, the display will show a "-".
		 */
		void setNumber(uint8_t number) const;

		/**
		 * @brief Turns the decimal point on or off.
		 * @param enable If true, decimal point is on. If false, decimal point is off.
		 */
		void setDecimalPoint(bool enable) const;

		/**
		 * @brief Turns als segments off.
		 */
		void clear(void) const;
  
	private:
		/**
		 * @brief Decides whether a given number is valid or not (valid means [0-9]).
		 * @param number The number to verify.
		 * @return True if valid, false otherwise.
		 */
		bool isNumberValid(uint8_t number) const;

		Device::pin_t segmentMap[9];
		Device::signal_t (* numberMap)[7];
		bool _hasDecimalPoint;
};

#endif
