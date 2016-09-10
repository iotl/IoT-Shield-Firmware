#include <ParkingShield.h>

/*  #define BUTTON_S1 A0
    #define LED_1 A4
*/
static const uint8_t BUTTON_S1=A0;
static const uint8_t LED_1=A4;

//siehe pins_arduino.h

void setup()
{
  /*
   * pinMode(pin, mode)
   * mode: INPUT, OUTPUT, or INPUT_PULLUP
  */
  pinMode(BUTTON_S1, INPUT);
  pinMode(LED_1, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //digitalWrite(pin, value)
  bool buttonPressed = digitalRead(BUTTON_S1);
  Serial.println(buttonPressed);
  digitalWrite(LED_1, !buttonPressed);
}


/* Auszug aus der  Arduino.h
void pinMode(uint8_t, uint8_t);
126 void digitalWrite(uint8_t, uint8_t);
127 int digitalRead(uint8_t);
128 int analogRead(uint8_t);
129 void analogReference(uint8_t mode);
130 void analogWrite(uint8_t, int);
*/
