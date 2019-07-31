//
// Created by Timothy Findlay on 2019-07-22.
//

#include "main.h"
#include <Arduino.h>
#include "wifi_setup.h"
#include "clock_setup.h"
#include "socket_comms.h"
#include "sound_sensor.h"
#include <driver/adc.h>
#include "http_log.h"
#include <RunningAverage.h>

RunningAverage minuteAverage(70); // 60 seconds, plus some wiggle room if it loops faster

// Configure timer...
unsigned long currentMillis;
unsigned long Millis;

#define LED_BUILTIN 2
static const adc1_channel_t channel = ADC1_CHANNEL_0;  //GPIO36 or ADC1
static const adc_atten_t atten = ADC_ATTEN_DB_0;

void setup()
{
    // Configure Serial Port for monitoring
    Serial.begin(115200);

    // Configure LED for blinking
    pinMode(LED_BUILTIN, OUTPUT);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(channel, atten);

    // Give the terminal enough time to connect
    delay(1000);
    setup_wifi();

    // Configure the clock
    delay(1000);
    setClock();
    minuteAverage.clear();
};

void loop()
{
    // Listen for the current noise level
    float dbValue = getNoiseLevel(1);

    // Add to average object
    minuteAverage.addValue(dbValue);

    if(CheckTime(Millis, 60000UL, true)) {
        // Wake up, send the average!
        // Provide feedback on the serial line
        Serial.print(dbValue,DEC);
        Serial.print(" or ");
        Serial.print(minuteAverage.getAverage());
        Serial.println(" dBA");

        // If this feature is enabled...
        if(LOGZ_IO_ENABLED) {
            // Send log level to Logz.io
            char* jsonPayload = prepare_payload(getTimestamp(),  WiFi.localIP().toString().c_str(), minuteAverage.getAverage());
            http_log(LOG_SERVER, LOG_PORT, LOG_URI, (char *)"SoundLevel", jsonPayload);
        }
    }

    // Test the level
    if(dbValue > 110) {

        // If this feature is enabled...
        if(LOGZ_IO_ENABLED) {
            // Send log level to Logz.io
            char* jsonPayload = prepare_payload(getTimestamp(),  WiFi.localIP().toString().c_str(), minuteAverage.getAverage());
            http_log(LOG_SERVER, LOG_PORT, LOG_URI, (char *)"ThresholdBreached", jsonPayload);
        }

        // Feature toggle found in secrets.h
        if(SMART_SWITCH_ENABLED) {

            // Flash the lights 5 times, 1 second delay on/off = 10 second effect
            for(int i = 0; i < 5; i++) {
                // This will send the command via TCP to the TP Link smart switch
                switch_on(UMBRELLA_SWITCH);

                // Add half a second delay before switching off
                delay(1000);

                // This will send the command via TCP to the TP Link smart switch
                switch_off(UMBRELLA_SWITCH);

                // Add half a second delay before looping (switching on)
                delay(1000);
            }
        }
    }
}
