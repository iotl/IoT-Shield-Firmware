#include <SoftwareSerial.h>
#include <Esp8266.h>
#include <IPDParser.h>
#include <HttpRequest.h>
#include <ParkingShield.h>

// CHANGE THE TALKBACK'S API KEY HERE:
static const char api_key[] = "V4OEUG5T1A0TFZLC";

// CHANGE THE TALKBACK ID HERE:
static const unsigned int talkbackId = 3391;

ParkingShield shield;
SoftwareSerial espSerial(2, 3);
Esp8266<SoftwareSerial> esp(espSerial);

void setup()
{
  Serial.begin(9600);

  // Setup module
  esp.configureBaud();
  esp.setBaud(9600);
  
  // Setting the module to wireless client(1) or access point mode(2) 
  // is not yet in API. We have to set it by an AT command.
  espSerial.print(F("AT+CWMODE=1\r\n"));

  esp.joinAccessPoint("IEKnet", "wlanIEKnet19");
  esp.setMultipleConnections(true);
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

  // Print the request
  String reqStr = req.get();
  Serial.print(F("Send request: "));
  Serial.println(reqStr);

  // Send the request
  esp.connect(1, F("api.thingspeak.com"), 80);
  esp.send(1, reqStr);

  // Parse answer
  IPDParser parser(espSerial);
  if (parser.parse()) 
  {
    String payload = parser.getPayload();
    Serial.print(F("Received talkback: "));
    Serial.println(payload);
    executeCommand(payload);
  }
  else
    Serial.println(F("No or invalid ansewer."));

  // Thingspeak requires 15 s delay between requests
  delay (16000);
}
