#include <SevenSeg.h>
#include <avr/pgmspace.h>

// -------------------------------------------------------------------------- //
// Helper
// -------------------------------------------------------------------------- //

// Specification for common cathode. We will change this in constructor if we have common anode.
Device::signal_t segmentstateMap[SevenSeg::NUMBER_SEGMENTSTATES] = { Device::SIGNAL_HIGH, Device::SIGNAL_LOW };

static bool const symbolMap[SevenSeg::NUMBER_SYMBOLS][SevenSeg::NUMBER_SEGMENTS] =
{
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

// -------------------------------------------------------------------------- //
// Private
// -------------------------------------------------------------------------- //
void SevenSeg::setupPins(Device::pin_t const segmentPins[])
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

void SevenSeg::setupSignals(connector_t connector) const
{
	switch (connector)
	{
		case CONNECTOR_COMMONANODE:
			segmentstateMap[SEGMENTSTATE_ON] = Device::SIGNAL_LOW;
			segmentstateMap[SEGMENTSTATE_OFF] = Device:: SIGNAL_HIGH;
			break;

		case CONNECTOR_COMMONCATHODE:
			segmentstateMap[SEGMENTSTATE_ON] = Device::SIGNAL_HIGH;
			segmentstateMap[SEGMENTSTATE_OFF] = Device:: SIGNAL_LOW;
			break;

		default:
			segmentstateMap[SEGMENTSTATE_ON] = Device::SIGNAL_LOW;
			segmentstateMap[SEGMENTSTATE_OFF] = Device:: SIGNAL_HIGH;
			break;
	}
}

// -------------------------------------------------------------------------- //
// Public
// -------------------------------------------------------------------------- //

SevenSeg::SevenSeg(Device::pin_t const segmentPins[], bool hasDecimalPoint, connector_t connector)
	:	_hasDecimalPoint(hasDecimalPoint)
{
	setupPins(segmentPins);
	setupSignals(connector);

	clear();
}

void SevenSeg::showNumber(uint8_t number)
{
	if (!isNumberValid(number))
		return;

	symbol_t symbol =  static_cast<symbol_t>(number);
	showSymbol(symbol);
}

void SevenSeg::showSymbol(symbol_t symbol)
{
	_symbol = symbol;
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

void SevenSeg::clear(void)
{
	showSymbol(SYMBOL_NOTHING);
	showDecimalPoint(false);
}

bool SevenSeg::isNumberValid(uint8_t number) const
{
	return number <= SYMBOL_9;
}

SevenSeg::symbol_t SevenSeg::symbol(void) const
{
	return _symbol;
}

char SevenSeg::number(void) const
{
	return isNumberValid(_symbol) ? _symbol : -1;
}

SevenSeg & SevenSeg::operator++(int)
{
	if (isNumberValid(_symbol))
		showNumber(number() + 1);
	return *this;
}

SevenSeg & SevenSeg::operator--(int)
{
	if (isNumberValid(_symbol))
		showNumber(number() - 1);
	return *this;
}
