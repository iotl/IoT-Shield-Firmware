#include <SoftwareSerial.h>

// Use the RX and TX pins of the ESP8266 WiFi module
SoftwareSerial espSerial(2,3); 

void setup() 
{
    Serial.begin(9600);
    espSerial.begin(9600);
}

void loop() 
{
  // Forward a byte form the WiFi UART -> USB UART
  if (espSerial.available()) {
    Serial.write(espSerial.read());
  }

  // Forward a byte form the USB UART -> WiFi UART
  if (Serial.available()) { 
    espSerial.write(Serial.read());
  }
}
