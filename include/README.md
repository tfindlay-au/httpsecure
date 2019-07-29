# Code blocks to make this program work

The following blocks of code have been separated out here for easy maintenance. This also makes it easier to test various libraries to do the HTTP connection to the API.

* secrets.h
* clock_setup.h
* wifi_setup.h
* dencrypt.h
* socket_comms.h
* sound_sensor.h

#### secrets.h
This file contains the nessasary enviuronment configuration values.

|value|Decscription|Example|
|-----|------------|-------|
|WIFI_SSID|Wifi Network name to connect to|MY_NETWORK|
|WIFI_PASS|PSK for the wifi network|MY_PASSWORD|
|UMBRELLA_SWITCH|IP Address of the TP Link Smart Switch|10.10.10.10|

#### clock_setup.h
This contains the logic to connect to an NTP server and set the correct clock on the device.

This is useful as the ESP32 does not have a realtime clock (RTC).

#### wifi_setup.h
This contains the code (using the Arduino WiFi.h library) to establish a connection to the wireless network.

The assigned (DHCP) IP address is printed to the serial console.

#### dencrypt.h
This provides methods to encrypt/decrypt the payload from the TP Link Smart Switch. The switch uses simple XOR method to obfuscate/de-obfuscate the payload.

The payloads are typically JSON strings which are well documented on the internet.

#### socket_comms.h
This provides a wrapper around dencrypt.h and establishes a socker layer connection to the TP Link device. In this case, 2 hard coded payloads are configurd to switch on and switch off the device.

#### sound_sensor.h
This provides a simple method to read a value from an analog port in the ESP32. In our example we have used a DF Robot Gravity Sound Level meter.
