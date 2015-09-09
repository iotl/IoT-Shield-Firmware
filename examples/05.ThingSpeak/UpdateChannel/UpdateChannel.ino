#include <Esp8266.h>
#include <SoftwareSerial.h>
#include <HttpRequest.h>

#include <ParkingShield.h>

// CHANGE CHANNEL'S API KEY HERE:
static const char api_key[] = "SSZQ72F4VTZW43YS";

ParkingShield shield;
SoftwareSerial espSerial(2,3);
Esp8266<SoftwareSerial> esp(espSerial);

void setup() 
{
  Serial.begin(9600);

  // Configure the module
  esp.configureBaud();
  esp.setBaud(9600);
  esp.joinAccessPoint("ti_iot","ti_iot42!");
  esp.setMultipleConnections(1);
}

void loop()
{
  // Read the temperature
  String temperature(shield.getTemperature());
  
  // Build the request
  HttpRequest req(F("/update"));
  req.addParameter(F("api_key"), api_key);  
  req.addParameter(F("field1"), temperature);

  // Print the request
  String reqStr = req.get();
  Serial.print("Send request: ");
  Serial.println(reqStr);

  // Send the request
  esp.connect(1, F("api.thingspeak.com"), 80);
  esp.send(1, reqStr);

  // Print answer
  Serial.print("Answer: ");
  Serial.println(espSerial.readString());
  
  // Thingspeak requires 15 s delay between requests 
  delay (16000);
}
