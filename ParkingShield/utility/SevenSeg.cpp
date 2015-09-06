#include "SevenSeg.h"

Device::signal_t numberMapAnode[12][7] = {
		{ Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW },	// 0
	    { Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW },		// 1
	    { Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_HIGH },	// 2
	    { Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH },	// 3
	    { Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },		// 4
	    { Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },	// 5
	    { Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },	// 6
	    { Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW },		// 7
	    { Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },	// 8
	    { Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },	// 9
		{ Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH },		// -
		{ Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW }			// nothing
	};

Device::signal_t numberMapCathode[12][7] = {
		{ Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH },		// 0
	    { Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },	// 1
	    { Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_LOW },		// 2
	    { Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW },	// 3
	    { Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW },		// 4
	    { Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW },		// 5
	    { Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW },		// 6
	    { Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH },		// 7
	    { Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW },			// 8
	    { Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_LOW, Device::SIGNAL_HIGH, Device::SIGNAL_LOW, Device::SIGNAL_LOW },		// 9
		{ Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_LOW },	// -
		{ Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH, Device::SIGNAL_HIGH }	// nothing
	};

SevenSeg::SevenSeg(Device::pin_t segmentPins[], bool anode, bool hasDecimalPoint)
	: numberMap(anode ? numberMapAnode : numberMapCathode), _hasDecimalPoint(hasDecimalPoint)
{
	for (uint8_t i = 0; i < 7; i++)
	{
		segmentMap[i] = segmentPins[i];
		Device::setPinMode(segmentMap[i], Device::PINMODE_OUTPUT);
	}
	if (_hasDecimalPoint)
	{
		segmentMap[7] = segmentPins[7];
		Device::setPinMode(segmentMap[7], Device::PINMODE_OUTPUT);
	}

	numberMap = anode ? numberMapAnode : numberMapCathode;

	clear();
}

void SevenSeg::setNumber(uint8_t number) const
{
	uint8_t numberMapIndex = number;
	if (!isNumberValid(number))
		numberMapIndex = 10;

	for(int i = 0; i < 7; i++)
		Device::digitalWritePin(segmentMap[i], numberMap[number][i]);
}

void SevenSeg::setDecimalPoint(bool enable) const
{
	//if (enable && hasDecimalPoint)
	//	Device::digitalWritePin(segmentMap[7+1], enable ? ON : OFF);
}

void SevenSeg::clear(void) const
{
	for(int i = 0; i < 7; i++)
		Device::digitalWritePin(segmentMap[i], numberMap[11][i]);
}

bool SevenSeg::isNumberValid(uint8_t number) const
{
	return number < 10;
}
