#include <ParkingShield.h>

// ---------------------------------------------------------------------------------------------------- //
// Helper
// ---------------------------------------------------------------------------------------------------- //
typedef enum
{
    BRIGHTNESS,
    TEMPERATURE,
    INPUT_MAX
} input_t;

typedef enum
{
    LED_GREEN = ParkingShield::GREEN_LED,
    LED_YELLOW = ParkingShield::YELLOW_LED,
    LED_RED = ParkingShield::RED_LED,
    BUZZER,
    OUTPUT_MAX
} output_t;

Device::pin_t const output_pins[OUTPUT_MAX] = {Device::DIGITAL_PIN_4, Device::ANALOG_PIN_5, Device::ANALOG_PIN_4, Device::DIGITAL_PIN_5};
Device::pin_t const input_pins[INPUT_MAX] = {Device::ANALOG_PIN_2, Device::ANALOG_PIN_3};
Device::pin_t const sevensegment_pins[8] = {Device::DIGITAL_PIN_7,Device::DIGITAL_PIN_8,Device::DIGITAL_PIN_9,Device::DIGITAL_PIN_10,Device::DIGITAL_PIN_11,Device::DIGITAL_PIN_12,Device::DIGITAL_PIN_13,Device::DIGITAL_PIN_6};

bool isInputPinValid(input_t inputPin)
{
    return inputPin < INPUT_MAX;
}

bool isOutputPinValid(output_t outputPin)
{
    return outputPin < OUTPUT_MAX;
}

bool isLedValid(ParkingShield::led_t led)
{
    return led < ParkingShield::LED_MAX;
}

void setPinMode(Device::pin_t pin, Device::pinmode_t pinmode)
{
    Device::setPinMode(pin, pinmode);
}

void setupOutput()
{
    for (unsigned int output = 0; output < OUTPUT_MAX; output++)
        setPinMode(output_pins[output], Device::PINMODE_OUTPUT);
}

void setupInput()
{
    for (unsigned int input = 0; input < INPUT_MAX; input++)
        setPinMode(input_pins[input], Device::PINMODE_INPUT);
}

unsigned int analogReadPin(input_t inputPin)
{
    if (isInputPinValid(inputPin))
        return Device::analogReadPin(input_pins[inputPin]);

    return 0;
}

void analogWritePin(output_t outputPin, uint8_t value)
{
    if (isOutputPinValid(outputPin))
        Device::analogWritePin(output_pins[outputPin], value);
}

Device::signal_t digitalReadPin(input_t inputPin)
{
    if (isInputPinValid(inputPin))
        return Device::digitalReadPin(input_pins[inputPin]);

    return Device::SIGNAL_LOW;
}

void digitalWritePin(output_t outputPin, Device::signal_t signal)
{
    if (isOutputPinValid(outputPin))
        Device::digitalWritePin(output_pins[outputPin], signal);
}

void ParkingShield::setLed(led_t led, bool enable)
{
    if (isLedValid(led))
        digitalWritePin(static_cast<output_t>(led), enable ? Device::SIGNAL_LOW : Device::SIGNAL_HIGH);
}

void setAllLeds(bool enable)
{
    for (unsigned int led = 0; led < ParkingShield::LED_MAX; led++)
        ParkingShield::setLed(static_cast<ParkingShield::led_t>(led), enable);
}

ParkingShield::Button::Button(Device::pin_t button_pin) : repeatInterval(0), pinNumber(button_pin)
{
    setPinMode(button_pin, Device::PINMODE_INPUT);
}

bool ParkingShield::Button::sampleButton()
{
    unsigned long time = Device::milliseconds();

    bool button_pressed = Device::digitalReadPin(pinNumber) == Device::SIGNAL_HIGH;

    if (button_pressed && time - repeatTime >= repeatInterval)
    {
        repeatTime = time;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------- //
// Public
// ---------------------------------------------------------------------------------------------------- //
ParkingShield::ParkingShield(void) : sevenSeg(sevensegment_pins),
            buttonS1(Device::ANALOG_PIN_0), buttonS2(Device::ANALOG_PIN_1)
{
    setupOutput();
    setupInput();

    setAllLeds(false);
}

void ParkingShield::setRepeatInterval(unsigned int interval)
{
    buttonS1.repeatInterval = interval;
    buttonS2.repeatInterval = interval;
}

bool ParkingShield::buttonS1Pressed(void)
{
  return buttonS1.sampleButton();
}

bool ParkingShield::buttonS2Pressed(void)
{
  return buttonS2.sampleButton();
}

unsigned int ParkingShield::getTemperature(void) const
{
    unsigned int tempVoltage = analogReadPin(TEMPERATURE);
    return (tempVoltage / 1024.0) * 5.0 * 100.0 - 5.0;
}

unsigned int ParkingShield::getBrightness(void) const
{
    return analogReadPin(BRIGHTNESS);
}

unsigned int ParkingShield::getAverageBrightness(void)
{
    brightnessValues[brightnessValuesPointer] = analogReadPin(BRIGHTNESS);
    brightnessValuesPointer++;
    brightnessValuesPointer %= BRIGHTNESS_ARRAY_SIZE;
    int average = 0;
    int i;
    for( i = 0; i < BRIGHTNESS_ARRAY_SIZE; ++i)
    {
        average += brightnessValues[i];
    }

    return average / BRIGHTNESS_ARRAY_SIZE;
}

void ParkingShield::setBuzzer(bool enable) const
{
    digitalWritePin(BUZZER, enable ? Device::SIGNAL_HIGH : Device::SIGNAL_LOW);
}

void ParkingShield::beep(int frequencyInHertz, long timeInMilliseconds) const
{
    int x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)
    {
        setBuzzer(true);
        Device::delayMicros(delayAmount);
        setBuzzer(false);
        Device::delayMicros(delayAmount);
    }

    Device::delayMillis(20);
}

void ParkingShield::playTone(int tone, int duration) const
{
    for (long i = 0; i < duration * 1000L; i += tone * 2)
    {
        setBuzzer(true);
        Device::delayMicros(tone);
        setBuzzer(false);
        Device::delayMicros(tone);
    }
}

void ParkingShield::playNote(char note, int duration) const
{
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++)
    {
        if (names[i] == note)
            playTone(tones[i], duration);
    }
}

void ParkingShield::playMarch(bool shortVersion) const
{
    int const c = 261;
    int const d = 294;
    int const e = 329;
    int const f = 349;
    int const g = 391;
    int const gS = 415;
    int const a = 440;
    int const aS = 455;
    int const b = 466;
    int const cH = 523;
    int const cSH = 554;
    int const dH = 587;
    int const dSH = 622;
    int const eH = 659;
    int const fH = 698;
    int const fSH = 740;
    int const gH = 784;
    int const gSH = 830;
    int const aH = 880;
    //frequencies for the tones we're going to use
    //used http://home.mit.bme.hu/~bako/tonecalc/tonecalc.htm to get these

    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note

    beep(a, 500);
    beep(a, 500);
    beep(a, 500);
    beep(f, 350);
    beep(cH, 150);

    beep(a, 500);
    beep(f, 350);
    beep(cH, 150);
    beep(a, 1000);
    //first bit

    beep(eH, 500);
    beep(eH, 500);
    beep(eH, 500);
    beep(fH, 350);
    beep(cH, 150);

    beep(gS, 500);
    beep(f, 350);
    beep(cH, 150);
    beep(a, 1000);

    if (shortVersion)
      return;

    //second bit...

    beep(aH, 500);
    beep(a, 350);
    beep(a, 150);
    beep(aH, 500);
    beep(gSH, 250);
    beep(gH, 250);

    beep(fSH, 125);
    beep(fH, 125);
    beep(fSH, 250);
    Device::delayMillis(250);
    beep(aS, 250);
    beep(dSH, 500);
    beep(dH, 250);
    beep(cSH, 250);
    //start of the interesting bit

    beep(cH, 125);
    beep(b, 125);
    beep(cH, 250);
    Device::delayMillis(250);
    beep(f, 125);
    beep(gS, 500);
    beep(f, 375);
    beep(a, 125);

    beep(cH, 500);
    beep(a, 375);
    beep(cH, 125);
    beep(eH, 1000);
    //more interesting stuff (this doesn't quite get it right somehow)

    beep(aH, 500);
    beep(a, 350);
    beep(a, 150);
    beep(aH, 500);
    beep(gSH, 250);
    beep(gH, 250);

    beep(fSH, 125);
    beep(fH, 125);
    beep(fSH, 250);
    Device::delayMillis(250);
    beep(aS, 250);
    beep(dSH, 500);
    beep(dH, 250);
    beep(cSH, 250);
    //repeat... repeat

    beep(cH, 125);
    beep(b, 125);
    beep(cH, 250);
    Device::delayMillis(250);
    beep(f, 250);
    beep(gS, 500);
    beep(f, 375);
    beep(cH, 125);

    beep(a, 500);
    beep(f, 375);
    beep(c, 125);
    beep(a, 1000);
}

void ParkingShield::playMelody(void) const
{
    static int length = 15; // the number of notes
    static char notes[] = "ccggaagffeeddc "; // a space represents a rest
    static int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
    static int tempo = 300;

    for (int i = 0; i < length; i++)
    {
        if (notes[i] == ' ') {
            Device::delayMillis(beats[i] * tempo); // rest
        } else {
            playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        Device::delayMillis(tempo / 2);
    }
}
