#include<ParkingShield.h>

const int PWM_LED = 3;
ParkingShield shield;
float temp;


void setup() 
{
  Serial.begin(9600);
  analogWrite(PWM_LED,255);
}

void loop() 
{ 
  temp=(float)shield.getBrightness()/1024 * 100;
  temp=255-(temp*255/100);
  
  Serial.println(shield.getBrightness());
  
  if(temp<25) analogWrite(PWM_LED,0);
  else analogWrite(PWM_LED,temp);

} 
