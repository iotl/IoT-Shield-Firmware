#include <Esp8266.h>
#include <SoftwareSerial.h>
#include <HttpRequest.h>

#include <ParkingShield.h>

// CHANGE CHANNEL'S API KEY HERE:
static const char api_key[] = "QWERTZASDFYXCV";

SoftwareSerial espSerial(2,3);
Esp8266<SoftwareSerial> esp(espSerial);
ParkingShield shield;

void setup() 
{
  Serial.begin(9600);
 
  esp.configureBaud();
  esp.joinAccessPoint("ti_iot","ti_iot42!");
  esp.setMultipleConnections(1);
}

void loop()
{
  String temperature(shield.getTemperature());
  
  // Build GET request
  HttpRequest req(F("/update"));
  req.addParameter(F("api_key"), api_key);  
  req.addParameter(F("field1"), temperature);

  // Build GET request string
  char getRequest[100];
  req.get(getRequest);

  Serial.printf("Request : %s", getRequest);

  // Send get request string
  esp.connect(1, F("api.thingspeak.com"), 80);
  esp.send(1, getRequest, strlen(getRequest));
  
  // Thingspeak requires 15 s delay between requests 
  delay (16000);
}
