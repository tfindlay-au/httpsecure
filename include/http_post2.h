//
// Created by Timothy Findlay on 2019-07-22.
//
// Using esp_http_client from:
//   https://platformio.org/lib/show/798/ArduinoHttpClient/examples
// Code:
//   https://github.com/arduino-libraries/ArduinoHttpClient
// Requires (in platformio.ini):
//   lib_deps = ArduinoHttpClient  ; by Adrian McEwen
// Status:
//   because the following virtual functions are pure within 'HttpClient'
//

#include <ArduinoHttpClient.h>
#include <WiFi101.h>

#ifndef HTTPSECURE_HTTP_POST2_H
#define HTTPSECURE_HTTP_POST2_H

const char *serverAddress = "https://postman-echo.com/post";  // server address
int port = 8443;

WiFiClient wifi;
HttpClient httpClient = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

static void send_https() {
    String postData = "foo1=bar1&foo2=bar2";

    httpClient.beginRequest();
    httpClient.post("/");
    httpClient.sendHeader("Content-Type", "application/x-www-form-urlencoded");
    httpClient.sendHeader("Content-Length", postData.length());
    httpClient.sendHeader("X-Custom-Header", "custom-header-value");
    httpClient.beginBody();
    httpClient.print(postData);
    httpClient.endRequest();

    // read the status code and body of the response
    int statusCode = httpClient.responseStatusCode();
    String response = httpClient.responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
}

#endif //HTTPSECURE_HTTP_POST2_H
