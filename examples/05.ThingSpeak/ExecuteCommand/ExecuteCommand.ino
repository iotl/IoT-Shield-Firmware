#include <SoftwareSerial.h>
#include <Esp8266.h>
#include <IPDParser.h>
#include <HttpRequest.h>
#include <ParkingShield.h>

// CHANGE THE TALKBACK ID AND API KEY HERE:
static const unsigned int talkbackId = 9999;
static const char api_key[] = "ABCDEFGHIJKLMNOP";

#define log(result,message) \
  (Serial.print(message), Serial.print(F(": ")), Serial.println(result))

ParkingShield shield;
SoftwareSerial espSerial(2, 3);
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

void executeCommand(const String &str)
{
  if (str == F("/led/1/on"))
    shield.setLed(ParkingShield::RED_LED, true);

  else if (str == F("/led/1/off"))
    shield.setLed(ParkingShield::RED_LED, false);

  else if (str == F("/led/2/on"))
    shield.setLed(ParkingShield::YELLOW_LED, true);

  else if (str == F("/led/2/off"))
    shield.setLed(ParkingShield::YELLOW_LED, false);

  else if (str == F("/led/3/on"))
    shield.setLed(ParkingShield::GREEN_LED, true);

  else if (str == F("/led/3/off"))
    shield.setLed(ParkingShield::GREEN_LED, false);
  
  else if (str == F("/buzzer/1/march"))
    shield.playMarch();

  else if (str == F("/buzzer/1/melody"))
    shield.playMelody();

  else if (str == F("/7seg/1/off"))
    shield.sevenSeg.clear();

  else if (str == F("/7seg/1/0"))
    shield.sevenSeg.showNumber(0);

  else if (str == F("/7seg/1/1"))
    shield.sevenSeg.showNumber(1);

  else if (str == F("/7seg/1/2"))
    shield.sevenSeg.showNumber(2);

  else if (str == F("/7seg/1/3"))
    shield.sevenSeg.showNumber(3);

  else if (str == F("/7seg/1/4"))
    shield.sevenSeg.showNumber(4);

  else if (str == F("/7seg/1/5"))
    shield.sevenSeg.showNumber(5);

  else if (str == F("/7seg/1/6"))
    shield.sevenSeg.showNumber(6);

  else if (str == F("/7seg/1/7"))
    shield.sevenSeg.showNumber(7);

  else if (str == F("/7seg/1/8"))
    shield.sevenSeg.showNumber(8);

  else if (str == F("/7seg/1/9"))
    shield.sevenSeg.showNumber(9);
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
  String reqStr = req.get();

  // Connect to thingspeak
  log(esp.connectSecure(1, F("api.thingspeak.com")), F("Connecting to thingspeak through TLS"));

  // Send the request
  log(reqStr, F("Send request"));
  esp.send(1, reqStr);

  // Parse answer
  IPDParser parser(espSerial);
  if (parser.parse()) {
    String payload = parser.getPayload();
    log(payload, F("Received talkback"));
    executeCommand(payload);
  } else {
    Serial.println(F("No or invalid answer."));
  }

  // Poll every 8 seconds for new commands
  delay(8000);
}
