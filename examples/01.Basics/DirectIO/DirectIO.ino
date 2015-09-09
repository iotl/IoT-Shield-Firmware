#define BUTTON_S1 A0
#define LED_1 A4

void setup()
{
  pinMode(BUTTON_S1, INPUT);
  pinMode(LED_1, OUTPUT);
}

void loop()
{
  bool buttonPressed;
  buttonPressed = digitalRead(BUTTON_S1);
  digitalWrite(LED_1, !buttonPressed);
}
