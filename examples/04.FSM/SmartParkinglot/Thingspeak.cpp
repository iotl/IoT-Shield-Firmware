#include "Thingspeak.h"

#define log(result,message) \
  (Serial.print(message), Serial.print(F(": ")), Serial.println(result))

void setupWlan(Esp8266<SoftwareSerial>& esp, const char* ssid, const char* psk) {
  log(esp.configureBaud(), F("Trying to find baud rate for WLAN module"));
  log(esp.setBaud(9600), F("Switch to 9600 baud"));

  log(esp.joinAccessPoint(ssid, psk), F("Connecting to the AP"));

  log(esp.setMultipleConnections(true), F("Enable multi-connection support"));
}

Talkback::Talkback(SoftwareSerial& serial, Esp8266<SoftwareSerial>& esp, Parkinglot& parkinglot, unsigned int apiId, const char* apiKey)
  : serial(serial), esp(esp), parkinglot(parkinglot), apiId(apiId), apiKey(apiKey)
{ }

void Talkback::update() {
  // Build the request path
  String path(F("/talkbacks/"));
  path += apiId;
  path += F("/commands/execute");

  // Build the request
  HttpRequest req(path);
  req.addParameter(F("api_key"), apiKey);
  String reqStr = req.get();

  // Connect to thingspeak
  log(esp.connectSecure(1, F("api.thingspeak.com")), F("Connecting to thingspeak through TLS"));

  // Send the request
  log(reqStr, F("Send request"));
  esp.send(1, reqStr);

  // Parse answer
  IPDParser parser(serial);
  if (parser.parse()) {
    String command = parser.getPayload();
    log(command, F("Received talkback"));

    if(command == "pay") {
      parkinglot.process(Parkinglot::pay);
    } else if(command == "start") {
      parkinglot.process(Parkinglot::start);
    }
  } else {
    Serial.println(F("No or invalid answer."));
  }
}

