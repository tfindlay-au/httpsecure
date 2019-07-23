//
// Created by Timothy Findlay on 2019-07-22.
//

#include "main.h"
#include <Arduino.h>
#include "wifi_setup.h"
#include "clock_setup.h"
//#include "http_post.h"
//#include "http_post2.h"
//#include "http_post3.h"
#include "http_post4.h"

void setup()
{
    // Configure Serial Port for monitoring
    Serial.begin(115200);

    // Configure LED for blinking
    pinMode(LED_BUILTIN, OUTPUT);

    // Give the terminal enough time to connect
    delay(1000);
    setup_wifi();

    // Configure the clock
    delay(1000);
    setClock();

    send_https();
};

void loop()
{
    // This will switch on the LED, applying 3.3v to the pin
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
