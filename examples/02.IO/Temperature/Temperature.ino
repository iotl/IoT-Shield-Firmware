#include <ParkingShield.h>
ParkingShield shield;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.print(F("Temperature is : " ));
  Serial.print(shield.getTemperature());
  Serial.println(" °C");
  
  delay(1000);
}
