#include <Arduino.h>
#include <SevenSeg.h>

const int SevenSeg::segmentsForNumbers[11][NUM_SEGMENTS] = {
	{SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF },			// 0
    {SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF },		// 1
    {SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_ON },		// 2
    {SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_ON },		// 3
    {SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON },		// 4
    {SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON },		// 5
    {SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON },			// 6
    {SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF },		// 7
    {SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON },			// 8
    {SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_ON, SEGMENT_LED_OFF, SEGMENT_LED_ON, SEGMENT_LED_ON },			// 9
	{SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_OFF, SEGMENT_LED_ON }		// -
};

// 7 integers. one pin number for each segment. {a, b, c, d, e, f, g, decimal point}
SevenSeg::SevenSeg(int pin_a, int pin_b, int pin_c, int pin_d, int pin_e, int pin_f, int pin_g, int pin_dp)
{
	segmentPins[0] = pin_a;
	segmentPins[1] = pin_b;
	segmentPins[2] = pin_c;
	segmentPins[3] = pin_d;
	segmentPins[4] = pin_e;
	segmentPins[5] = pin_f;
	segmentPins[6] = pin_g;
	//segmentPins = {pin_a, pin_b, pin_c, pin_d, pin_e, pin_f, pin_g};
	for(int i = 0; i < NUM_SEGMENTS; ++i)
	{
		pinMode(segmentPins[i], OUTPUT);
		digitalWrite(segmentPins[i], SEGMENT_LED_OFF);
	}
  pinMode(pin_dp, OUTPUT);
	this->pin_dp = pin_dp;
	digitalWrite(pin_dp, SEGMENT_LED_OFF);
}

void SevenSeg::setNumber(int num)
{
	int number = num;
	// If we have an invalid value show a "-" on the display.
	if (number < 0 || number > 9)
		number = 10;
	//segmentValues values = segmentsForNumbers[number];
	for(int i = 0; i < NUM_SEGMENTS; ++i)
	{
		digitalWrite(segmentPins[i], segmentsForNumbers[number][i]);
		//digitalWrite(segmentPins[i], values.segments[i]);
	}
}
