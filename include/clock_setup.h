//
// Created by Timothy Findlay on 2019-07-22.
//

#ifndef HTTPSECURE_CLOCK_SETUP_H
#define HTTPSECURE_CLOCK_SETUP_H

void setClock() {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print(F("Waiting for NTP time sync: "));
    time_t nowSecs = time(nullptr);
    while (nowSecs < 8 * 3600 * 2) {
        delay(500);
        Serial.print(F("."));
        yield();
        nowSecs = time(nullptr);
    }

    Serial.println();
    struct tm timeinfo;
    gmtime_r(&nowSecs, &timeinfo);
    Serial.print(F("Current time: "));
    Serial.print(asctime(&timeinfo));
}

#endif //HTTPSECURE_CLOCK_SETUP_H
