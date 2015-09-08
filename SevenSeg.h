#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <DeviceArduino.h>
//#include <DeviceEmulator.h>
#include <stdint.h>


/**
 * @brief The SevenSeg class provides functionality to show the digits [0-9] and the decimal point on a single 7-segment display.
 * @author Marc Vester (XaserLE)
 */
class SevenSeg
{
	public:
		typedef enum
		{
			CONNECTOR_COMMONANODE,
			CONNECTOR_COMMONCATHODE,
			NUMBER_CONNECTORS
		} connector_t;

		typedef enum
		{
			SYMBOL_0,
			SYMBOL_1,
			SYMBOL_2,
			SYMBOL_3,
			SYMBOL_4,
			SYMBOL_5,
			SYMBOL_6,
			SYMBOL_7,
			SYMBOL_8,
			SYMBOL_9,
			SYMBOL_MINUS,
			SYMBOL_NOTHING,
			NUMBER_SYMBOLS
		} symbol_t;

		typedef enum
		{
			SEGMENT_A,
			SEGMENT_B,
			SEGMENT_C,
			SEGMENT_D,
			SEGMENT_E,
			SEGMENT_F,
			SEGMENT_G,
			NUMBER_SEGMENTS
		} segment_t;

		typedef enum
		{
			SEGMENTSTATE_ON,
			SEGMENTSTATE_OFF,
			NUMBER_SEGMENTSTATES
		} segmentstate_t;

		/**
		 * @brief Constructor
		 * @brief		 ---a---
		 * @brief		|				|
		 * @brief		|f			|b
		 * @brief		|				|
		 * @brief		 ---g---
		 * @brief		|				|
		 * @brief		|e			|c
		 * @brief		|				|
		 * @brief		 ---d---(dp)
		 * @param segmentPins An array with the device pins that are connected to the display, starting with 'a' and ending with 'g'. See above for order. Length: [7-8], dependent on the decimal point.
		 * @param hasDecimalPoint Indicates whether we have a decimal point on the display or not.
		 * @param connector Specifies the connector type of the display.
		 */
		SevenSeg(Device::pin_t const segmentPins[], bool hasDecimalPoint = true, connector_t connector = CONNECTOR_COMMONANODE);

		/**
		 * @brief Shows a number on the display.
		 * @param num The number to show. Valid values: [0-9]. If num is invalid, the display will show a "-".
		 */
		void showNumber(uint8_t number);

		/**
		 * @brief Shows a symbol (see enum above) on the display (more low level access as showNumber()).
		 * @param symbol The symbol to show.
		 */
		void showSymbol(symbol_t symbol);

		/**
		 * @brief Shows/hides a segment (show enum above) on the display (more low level access as showNumber() and showSymbol()).
		 * @brief Keep in mind that only this segment is turned on/off, all other segments remain untouched.
		 * @param segment The segment to show/hide.
		 * @param enable Indicates whether the segment is turned on or off.
		 */
		void showSegment(segment_t segment, bool enable = true) const;

		/**
		 * @brief Turns the decimal point on or off.
		 * @param enable If true, decimal point is on. If false, decimal point is off.
		 */
		void showDecimalPoint(bool enable = true) const;

		/**
		 * @brief Turns als segments off.
		 */
		void clear(void);

		/**
		 * @brief Decides whether a given number is valid or not (valid means [0-9]).
		 * @param number The number to verify.
		 * @return True if valid, false otherwise.
		 */
		bool isNumberValid(uint8_t number) const;

		/**
		 * @brief The currently shown symbol.
		 * @return Returns the currently shown symbol.
		 */
		symbol_t symbol(void) const;


		/**
		 * @brief The currently shown decimal digit.
		 * @return Returns the currently decimal digit. If no digit is shown -1 is returned.
		 */
		char number(void) const;

		/**
		 * @brief Postfix, increments the number on the seven segment display. If no number is shown, nothing will happen.
		 * @param right The object to increment.
		 * @return 
		 */
		SevenSeg & operator++(int);

		/**
		 * @brief Postfix, decrements the number on the seven segment display. If no number is shown, nothing will happen.
		 * @param right The object to increment.
		 * @return 
		 */
		SevenSeg & operator--(int);

	private:
		/**
		 * @brief Saves all pins and sets them to output.
		 * @param segmentPins The array that maps segments a-g to device pins.
		 */
		void setupPins(Device::pin_t const segmentPins[]);

		/**
		 * @brief Sets up the signals.
		 * @param connector Connector type of the display.
		 */
		void setupSignals(connector_t connector) const;

		// Holds the mapping from segments to device pins.
		Device::pin_t segmentMap[NUMBER_SEGMENTS];
		// We put the pin for the decimal point in a separate variable.
		bool _hasDecimalPoint;
		Device::pin_t decimalPointPin;
		symbol_t _symbol;
};

#endif
