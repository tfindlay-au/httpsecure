//
// Created by Timothy Findlay on 2019-07-29.
//

#ifndef HTTPSECURE_SOUND_SENSOR_H
#define HTTPSECURE_SOUND_SENSOR_H

#define SOUND_SENSOR_PIN 36
#define VREF  3.3  //voltage on AREF pin,default:operating voltage

/** @brief Capture analog input and return approximate reading
 * @retval float value containing approximate DB noise level
 *
 */
static float displayNoise() {

    float voltageValue,dbValue;
    voltageValue = analogRead(SOUND_SENSOR_PIN) / 1024.0 * VREF;
    dbValue = voltageValue * 20.0;
    return dbValue;
}


#endif //HTTPSECURE_SOUND_SENSOR_H
