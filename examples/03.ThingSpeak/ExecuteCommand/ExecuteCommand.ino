#include <SoftwareSerial.h>

#include <Esp8266.h>
#include <IPDParser.h>
#include <HttpRequest.h>
#include <ParkingShield.h>

// CHANGE THE TALKBACK'S API KEY HERE:
static const char api_key[] = "WDE49XOAQE08C604";

// CHANGE THE TALKBACK ID HERE:
static const unsigned int talkbackId = 3092;

SoftwareSerial espSerial(2,3);
Esp8266<SoftwareSerial> esp(espSerial);
ParkingShield shield;

void setup() 
{
  Serial.begin(9600);

  // Setup module
  esp.configureBaud();
  esp.setBaud(9600);
  esp.joinAccessPoint("ti_iot","ti_iot42!");
  esp.setMultipleConnections(1);
}

void loop()
{
  // Build the request path
  String path(F("/talkbacks/"));
  path += talkbackId;
  path += F("/commands/execute");

  // Build the request
  HttpRequest req(path);
  req.addParameter(F("api_key"), api_key);  

  // Print the request
  String reqStr = req.get(); 
  Serial.print("Send request: ");
  Serial.println(reqStr);

  // Send the request
  esp.connect(1, F("api.thingspeak.com"), 80);
  esp.send(1, reqStr);

  // Parse answer
  IPDParser parser(espSerial);
  if (parser.parse()) {
    Serial.print("Received talkback: ");
    Serial.println(parser.getPayload());
  }
  else
    Serial.println("No or invalid ansewer.");
  
  // Thingspeak requires 15 s delay between requests 
  delay (16000);
}
