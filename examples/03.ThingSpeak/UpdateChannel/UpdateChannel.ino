#include <Esp8266.h>
#include <SoftwareSerial.h>
#include <HttpRequest.h>

#include <ParkingShield.h>

// CHANGE CHANNEL'S API KEY HERE:
static const char api_key[] = "SSZQ72F4VTZW43YS";

SoftwareSerial espSerial(2,3);
Esp8266<SoftwareSerial> esp(espSerial);
ParkingShield shield;

void setup() 
{
  Serial.begin(9600);
 
  esp.configureBaud();
  esp.setBaud(9600);
  esp.joinAccessPoint("ti_iot","ti_iot42!");
  esp.setMultipleConnections(1);
}

void loop()
{
  String temperature(shield.getTemperature());
  String host(F("api.thingspeak.com"));
  
  // Build GET request
  HttpRequest req(F("/update"));
  req.addParameter(F("api_key"), api_key);  
  req.addParameter(F("field1"), temperature);

  // Build GET request string
  char reqStr[100];
  req.get(reqStr);

  Serial.print("Send request: ");
  Serial.println(reqStr);

  // Send get request string
  esp.connect(1, host, 80);
  esp.send(1, reqStr, strlen(reqStr));

  Serial.print("Answer: ");
  Serial.println(espSerial.readString());
  
  // Thingspeak requires 15 s delay between requests 
  delay (16000);
}
