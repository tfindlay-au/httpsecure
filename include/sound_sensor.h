//
// Created by Timothy Findlay on 2019-07-29.
//

#ifndef HTTPSECURE_SOUND_SENSOR_H
#define HTTPSECURE_SOUND_SENSOR_H

#define SOUND_SENSOR_PIN 36
#define VREF  3.3  //voltage on AREF pin,default:operating voltage

/**
 * @brief Capture analog input and return approximate reading
 * @retval float value containing approximate DB noise level
 */
static float getNoiseLevel(int sensor_type) {
    float voltageValue, dbValue;
    voltageValue = analogRead(SOUND_SENSOR_PIN);

    // If the sensor resembles a DFRobot SEN0232 ....
    if(sensor_type == 1) {
        dbValue = (voltageValue / 1024.0 * VREF) * 15.0;
    } else {
        dbValue = (voltageValue + 83.2073) / 11.003;
    }
    return dbValue;
}


#endif //HTTPSECURE_SOUND_SENSOR_H
