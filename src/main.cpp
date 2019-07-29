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
};

void loop()
{
    // Listen for the current noise level
    float dbValue = displayNoise();

    // Provide feedback on the serial line
    Serial.print(dbValue,1);
    Serial.println(" dBA");

    // Test the level
    if(dbValue > 120) {

        Serial.println("  Triggered lights!");

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
