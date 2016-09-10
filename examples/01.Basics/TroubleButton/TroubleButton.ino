#include <ParkingShield.h>

/*  #define BUTTON_S1 A0
    #define LED_1 A4
*/
static const uint8_t PinDefSet        =A0;
static const uint8_t PinDefReset      =A1;
static const uint8_t PinDefLedRed     =A4;
static const uint8_t PinDefLedYellow  =A5;

int TureCounter=0;
bool pressed = false;

//siehe pins_arduino.h

void setup()
{
  /*
   * wesentliche Funktionsdeklerationen
   * 
   * pinMode(pin, mode)
   *    mode: INPUT, OUTPUT, or INPUT_PULLUP
   * 
   * digitalWrite(pin, value)
  */
  
  pinMode(PinDefSet,      INPUT);
  pinMode(PinDefReset,    INPUT);
  pinMode(PinDefLedRed,   OUTPUT);
  pinMode(PinDefLedYellow, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

  if(digitalRead(PinDefSet) && pressed==false)
  {
    TureCounter++;
    pressed=true;
    digitalWrite(PinDefLedRed, 0);
    Serial.println(TureCounter);
  }
  else 
  if(!digitalRead(PinDefSet))
  {
    digitalWrite(PinDefLedRed, 1);
    pressed=false;
  }
  
  //Reset Counter, Yellow LED
  if(digitalRead(PinDefReset))
  {
    if(TureCounter!=0)
    {
      TureCounter=0;
      Serial.println(TureCounter); 
    }
    digitalWrite(PinDefLedYellow,0);
  }
  else digitalWrite(PinDefLedYellow,1);
}
