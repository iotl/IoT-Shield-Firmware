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
    { true, true, true, false, true, true, true },		// A
    { false, false, true, true, true, true, true },		// b
    { true, false, false, true, true, true, false },	// C
    { false, false, false, true, true, false, true },	// c
    { false, true, true, true, true, false, true },		// d
    { true, false, false, true, true, true, true },		// E
    { true, false, false, false, true, true, true },	// F
    { false, true, true, false, true, true, true },		// H
    { false, false, true, false, true, true, true },	// h
    { false, false, false, false, true, true, false },	// I
    { false, false, false, true, true, true, false },	// L
    { false, false, false, false, true, true, false },  // l
    { true, true, true, true, true, true, false },		// O
    { false, false, true, true, true, false, true },	// o
    { true, true, false, false, true, true, true },		// P
    { true, false, true, true, false, true, true },		// S
    { false, true, true, true, true, true, false },		// U
    { false, false, true, true, true, false, false },	// u
    { false, true, true, true, false, true, true },		// Y
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

void SevenSeg::showChar(char c)
{
  symbol_t symbol;

  if (c == '0')
    symbol = SYMBOL_0;
  else if (c == '1')
    symbol = SYMBOL_1;
  else if (c == '2')
    symbol = SYMBOL_2;
  else if (c == '3')
    symbol = SYMBOL_3;
  else if (c == '4')
    symbol = SYMBOL_4;
  else if (c == '5')
    symbol = SYMBOL_5;
  else if (c == '6')
    symbol = SYMBOL_6;
  else if (c == '7')
    symbol = SYMBOL_7;
  else if (c == '8')
    symbol = SYMBOL_8;
  else if (c == '9')
    symbol = SYMBOL_9;
  else if (c == 'A')
    symbol = SYMBOL_A;
  else if (c == 'b')
    symbol = SYMBOL_b;
  else if (c == 'C')
    symbol = SYMBOL_C;
  else if (c == 'c')
    symbol = SYMBOL_c;
  else if (c == 'd')
    symbol = SYMBOL_d;
  else if (c == 'E')
    symbol = SYMBOL_E;
  else if (c == 'F')
    symbol = SYMBOL_F;
  else if (c == 'H')
    symbol = SYMBOL_H;
  else if (c == 'h')
    symbol = SYMBOL_h;
  else if (c == 'I')
    symbol = SYMBOL_I;
  else if (c == 'L')
    symbol = SYMBOL_L;
  else if (c == 'l')
    symbol = SYMBOL_l;
  else if (c == 'O')
    symbol = SYMBOL_O;
  else if (c == 'o')
    symbol = SYMBOL_o;
  else if (c == 'P')
    symbol = SYMBOL_P;
  else if (c == 'S')
    symbol = SYMBOL_S;
  else if (c == 'U')
    symbol = SYMBOL_U;
  else if (c == 'u')
    symbol = SYMBOL_u;
  else if (c == 'Y')
    symbol = SYMBOL_Y;
  else if (c == '-')
    symbol = SYMBOL_MINUS;
  else if (c == ' ')
    symbol = SYMBOL_NOTHING;
  else
    symbol = SYMBOL_MINUS;
  
  showSymbol(symbol);
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

SevenSeg & SevenSeg::operator++(void)
{
    if (isNumberValid(_symbol))
        showNumber(number() + 1);
    return *this;
}

SevenSeg & SevenSeg::operator--(void)
{
    if (isNumberValid(_symbol))
        showNumber(number() - 1);
    return *this;
}
