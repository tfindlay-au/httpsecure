//
// Created by Timothy Findlay on 2019-07-22.
//
#include "WiFi.h"
#include "secrets.h"

#ifndef HTTPSECURE_WIFISETUP_H
#define HTTPSECURE_WIFISETUP_H

void setup_wifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        if (WiFi.status() == WL_CONNECT_FAILED)
        {
            Serial.println();
            Serial.print("WiFi connection failed, re-attempting");
        }
        delay(500);
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address is ");
    Serial.println(WiFi.localIP());
}

#endif //HTTPSECURE_WIFISETUP_H
