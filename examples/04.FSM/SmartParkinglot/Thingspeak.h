#ifndef THINGSPEAK_H
#define THINGSPEAK_H

#include <Task.h>
#include <IPDParser.h>
#include <HttpRequest.h>
#include <Esp8266.h>

#define log(result,message) \
  (Serial.print(message), Serial.print(F(": ")), Serial.println(result))

template<class T>
void setupWlan(Esp8266<T>& esp, const char* ssid, const char* psk) {
  log(esp.configureBaud(), F("Trying to find baud rate for WLAN module"));
  log(esp.setBaud(9600), F("Switch to 9600 baud"));

  log(esp.joinAccessPoint(ssid, psk), F("Connecting to the AP"));

  log(esp.setMultipleConnections(true), F("Enable multi-connection support"));
}

template<class T>
class Talkback : public Task {
  public:
    using CommandCallback = void (*)(String);

    Talkback(Esp8266<T>& esp, unsigned int apiId, const char* apiKey, CommandCallback callback)
      : esp(esp), apiId(apiId), apiKey(apiKey), callback(callback) { }

    void update() {
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
      IPDParser parser(esp.getSerial());
      if (parser.parse()) {
        String command = parser.getPayload();
        log(command, F("Received talkback"));

        callback(command);
      } else {
        Serial.println(F("No or invalid answer."));
      }
    }

  private:
    Esp8266<T>& esp;
    CommandCallback callback;
    unsigned int apiId;
    const char* apiKey;
};

#undef log

#endif
