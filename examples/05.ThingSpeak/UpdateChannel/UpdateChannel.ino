#include <SoftwareSerial.h>
#include <Esp8266.h>
#include <HttpRequest.h>
#include <ParkingShield.h>

// CHANGE THE CHANNEL API KEY HERE:
static const char api_key[] = "ABCDEFGHIJKLMNOP";

#define log(result,message) \
  (Serial.print(message), Serial.print(F(": ")), Serial.println(result))

ParkingShield shield;
SoftwareSerial espSerial(2,3);
Esp8266<SoftwareSerial> esp(espSerial);

void setup() 
{
  Serial.begin(9600);

  // Configure the WLAN module
  log(esp.configureBaud(), F("Trying to find baud rate for WLAN module"));
  log(esp.setBaud(9600), F("Switch to 9600 baud"));

  log(esp.joinAccessPoint("eduinfo", ""), F("Connecting to the AP"));

  log(esp.setMultipleConnections(true), F("Enable multi-connection support"));
}

void loop()
{
  // Read the temperature
  String temperature(shield.getTemperature());

  // Build the request
  HttpRequest req(F("/update"));
  req.addParameter(F("api_key"), api_key);
  req.addParameter(F("field1"), temperature);
  String reqStr = req.get();

  // Connect to thingspeak
  log(esp.connectSecure(1, F("api.thingspeak.com")), F("Connecting to thingspeak through TLS"));

  // Send the request
  log(reqStr, F("Send request"));
  esp.send(1, reqStr);

  // Print answer
  log(espSerial.readString(), F("Answer"));

  // Thingspeak requires a 15 second delay between channel updates
  delay(15000);
}
