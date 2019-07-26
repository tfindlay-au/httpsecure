//
// Created by Timothy Findlay on 2019-07-22.
//

#include <WiFi.h>
#include "dencrypt.h"

#ifndef HTTPSECURE_HTTP_POST5_H
#define HTTPSECURE_HTTP_POST5_H

WiFiClient wiFiClient;

/**
 * @brief Control the smart switch at a given address and turn the device off
 * @param device_ip
 */
static void switch_on(const char *device_ip)
{
    const char command[] = "{\"system\":{\"set_relay_state\":{\"state\":1}}}";

    Serial.print("Connecting to: ");
    Serial.println(device_ip);

    if (wiFiClient.connect(device_ip, 9999)) {
        Serial.println("connected");

        unsigned char* payload = NULL;
        //unsigned char* output_address =
        encrypt(command, payload, sizeof(command));

        Serial.print("Result:");
        Serial.println((char*)payload);

        // Send the switch-on message
        wiFiClient.write((char*)payload);

        wiFiClient.flush();

        // Process the result
        const unsigned char* raw_result = NULL;
        if ( wiFiClient.available() ) {
            char c = wiFiClient.read();
            raw_result += c;
        }
        char* result = NULL;
        decrypt(raw_result, result, sizeof(raw_result));

        // Display the output on the serial console
        Serial.println(result);

    };

    wiFiClient.stop();
}

/**
 * @brief Control the smart switch at a given address and turn the device off
 * @param device_ip
 */
static void switch_off(const char *device_ip)
{
    const char command[] = "{\"system\":{\"set_relay_state\":{\"state\":0}}}";

    Serial.print("Connecting to: ");
    Serial.println(device_ip);

    if (wiFiClient.connect(device_ip, 9999)) {
        Serial.println("connected");

        unsigned char* payload = NULL;
        encrypt(command, payload, sizeof(command));
        Serial.print("Result:");
        Serial.println((char*)payload);

        // Send the switch-on message
        wiFiClient.write((char*)payload);

        wiFiClient.flush();

        // Display the result
        const unsigned char* raw_result = NULL;
        if ( wiFiClient.available() ) {
            char c = wiFiClient.read();
            raw_result += c;
        }
        char* result = NULL;
        decrypt(raw_result, result, sizeof(raw_result));

        Serial.println(result);
    };

    wiFiClient.stop();
}


#endif //HTTPSECURE_HTTP_POST5_H
