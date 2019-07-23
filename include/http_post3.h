//
// Created by Timothy Findlay on 2019-07-22.
//
// Using esp_http_client from:
//   https://platformio.org/lib/show/64/ArduinoJson/
//   https://arduinojson.org/v6/example/http-client/
// Code:
//   https://github.com/bblanchon/ArduinoJson.git
// Requires (in platformio.ini):
//   lib_deps = ArduinoJson
// Status:
//   No HTTPS support

#include <ArduinoJson.h>

#ifndef HTTPSECURE_HTTP_POST3_H
#define HTTPSECURE_HTTP_POST3_H


static void send_https()
{
    WiFiClient wifiClient;

    if (!wifiClient.connect("https://postman-echo.com/post", 8443)) {
        Serial.println(F("Connection failed"));
        return;
    }

    Serial.println(F("Connected!"));

    // Send HTTP request
    client.println(F("GET /example.json HTTP/1.0"));
    client.println(F("Host: arduinojson.org"));
    client.println(F("Connection: close"));
    if (client.println() == 0) {
        Serial.println(F("Failed to send request"));
        return;
    }
}

#endif //HTTPSECURE_HTTP_POST3_H
