#include <SoftwareSerial.h>

#include <Esp8266.h>
#include <IPDParser.h>
#include <HttpRequest.h>
#include <ParkingShield.h>

// CHANGE THE TALKBACK'S API KEY HERE:
static const char api_key[] = "WDE49XOAQE08C604";

// CHANGE THE TALKBACK ID HERE:
static const unsigned int talkbackId = 3092;

ParkingShield shield;
SoftwareSerial espSerial(2, 3);
Esp8266<SoftwareSerial> esp(espSerial);

void setup()
{
  Serial.begin(9600);

  // Setup module
  esp.configureBaud();
  esp.setBaud(9600);
  esp.joinAccessPoint("ti_iot", "ti_iot42!");
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
    String payload = parser.getPayload();
    Serial.print("Received talkback: ");
    Serial.println(payload);
    executeCommand(payload);
  }
  else
    Serial.println("No or invalid ansewer.");

  // Thingspeak requires 15 s delay between requests
  delay (16000);
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

  else if (str == F("/7seg/1/0"))
    shield.showNumber(0);

  else if (str == F("/7seg/1/1"))
    shield.showNumber(1);

  else if (str == F("/7seg/1/2"))
    shield.showNumber(2);

  else if (str == F("/7seg/1/3"))
    shield.showNumber(3);

  else if (str == F("/7seg/1/4"))
    shield.showNumber(4);

  else if (str == F("/7seg/1/5"))
    shield.showNumber(5);

  else if (str == F("/7seg/1/6"))
    shield.showNumber(6);

  else if (str == F("/7seg/1/7"))
    shield.showNumber(7);

  else if (str == F("/7seg/1/8"))
    shield.showNumber(8);

  else if (str == F("/7seg/1/9"))
    shield.showNumber(9);

  else if (str == F("/7seg/1/down"))
    shield.countDown();
}


