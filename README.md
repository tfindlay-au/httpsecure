# httpsecure

#### Overview
This project was formulated out of a desire to manage the noise levels in open plan offices using affordable components.

#### The plan
For a device to "listen" to the ambient sound level and if it exceeds a given level then trigger a switch to control some lights.

For this proof of concept we used an ESP32 device with a sound sensor level to control a TP Link Smart Switch.

Once triggered, the lights pulse at 1 second intervals for 5 cycles (10 seconds). This is sufficient to get the attention of noisy people and indicate that the should be quieter.

#### Out Of Scope
Ideas included controlling the TP Link HS-100 Smart Switch via the TP Link Cloud service. However due to the proprietary nature of the service this route was abandoned.

Further ideas included controlling Phillips Hue lights or Lifx lights.

#### Getting started
You will need the following hardware:
* https://www.dfrobot.com/product-1590.html
* https://www.dfrobot.com/product-83.html
* https://www.tp-link.com/au/home-networking/smart-plug/hs100/

You will need the following software:
* https://platformio.org/

Connecting it all together, the project is configured to have the sound sensor connected to pin GPIO 36 (ADC1_0)

#### Building
Using platform IO (we choose the CLI version opting for our own text editor)
```
$ pio run
```

#### Deploying
In this step, we bundle the command to:
 * compile
 * upload
 * monitor the serial port
```
# pio run --target=upload; pio device monitor
```

#### Packaging
Once you are happy with the operation, the ESP32 can be run from any 5v USB source (plug-pack, power bank or similar)

