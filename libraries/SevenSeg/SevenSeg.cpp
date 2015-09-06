#include <SevenSeg.h>

bool symbolMap[SevenSeg::NUMBER_SYMBOLS][SevenSeg::NUMBER_SEGMENTS] = {
		{ true, true, true, true, true, true, false },		// 0
	    { false, true, true, false, false, false, false },	// 1
	    { true, true, false, true, true, false, true },		// 2
	    { true, true, true, true, false, false, true },		// 3
	    { false, true, true, false, false, true, true },	// 4
	    { true, false, true, true, false, true, true },		// 5
	    { true, false, true, true, true, true, true },		// 6
	    { true, true, true, false, false, false, false },	// 7
	    { true, true, true, true, true, true, true },		// 8
	    { true, true, true, true, false, true, true },		// 9
		{ false, false, false, false, false, false, true },	// -
		{ false, false, false, false, false, false, false }	// nothing
	};

// Specification for common cathode. We will change this in constructor if we have common anode.
Device::signal_t segmentstateMap[SevenSeg::NUMBER_SEGMENTSTATES] = { Device::SIGNAL_HIGH, Device::SIGNAL_LOW };

SevenSeg::SevenSeg(Device::pin_t segmentPins[], bool hasDecimalPoint, connector_t connector) : _hasDecimalPoint(hasDecimalPoint)
{
	setupPins(segmentPins);

	switch (connector)
	{
		case CONNECTOR_COMMONANODE:		segmentstateMap[SEGMENTSTATE_ON] = Device::SIGNAL_LOW;
										segmentstateMap[SEGMENTSTATE_OFF] = Device:: SIGNAL_HIGH;
										break;
		case CONNECTOR_COMMONCATHODE:	segmentstateMap[SEGMENTSTATE_ON] = Device::SIGNAL_HIGH;
										segmentstateMap[SEGMENTSTATE_OFF] = Device:: SIGNAL_LOW;
										break;
		default:						segmentstateMap[SEGMENTSTATE_ON] = Device::SIGNAL_LOW;
										segmentstateMap[SEGMENTSTATE_OFF] = Device:: SIGNAL_HIGH;
										break;
	}

	clear();
}

void SevenSeg::showNumber(uint8_t number) const
{
	symbol_t symbol = SYMBOL_NOTHING;

	if (isNumberValid(number))
		symbol = static_cast<symbol_t>(number);
	else
		symbol = SYMBOL_MINUS;

	showSymbol(symbol);
}

void SevenSeg::showSymbol(symbol_t symbol) const
{
	for(int i = 0; i < NUMBER_SEGMENTS; i++)
		showSegment(static_cast<segment_t>(i), symbolMap[symbol][i]);
}

void SevenSeg::showSegment(segment_t segment, bool enable) const
{
	Device::digitalWritePin(segmentMap[segment], enable ? segmentstateMap[SEGMENTSTATE_ON] : segmentstateMap[SEGMENTSTATE_OFF]);
}

void SevenSeg::showDecimalPoint(bool enable) const
{
	Device::digitalWritePin(decimalPointPin, enable ? segmentstateMap[SEGMENTSTATE_ON] : segmentstateMap[SEGMENTSTATE_OFF]);
}

void SevenSeg::clear(void) const
{
	showSymbol(SYMBOL_NOTHING);
}

bool SevenSeg::isNumberValid(uint8_t number) const
{
	return number <= 9;
}

void SevenSeg::setupPins(Device::pin_t segmentPins[])
{
	for (uint8_t i = 0; i < NUMBER_SEGMENTS; i++)
	{
		segmentMap[i] = segmentPins[i];
		Device::setPinMode(segmentMap[i], Device::PINMODE_OUTPUT);
	}

	if (_hasDecimalPoint)
	{
		decimalPointPin = segmentPins[NUMBER_SEGMENTS];
		Device::setPinMode(decimalPointPin, Device::PINMODE_OUTPUT);
	}
}
