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

char* getTimestamp() {
    char* time_string = (char *)calloc(18, sizeof(char));
    time_t nowSecs = time(nullptr);
    struct tm timeinfo;
    gmtime_r(&nowSecs, &timeinfo);
    strftime(time_string,18,"%Y%m%d %H:%M:%S", &timeinfo);
    return time_string;
}

/**
 * Delay time expired function
 * @param lastMillis time we started
 * @param wait time we started
 * @param restart do we start again
 * @return
 */
boolean CheckTime(unsigned long &lastMillis, unsigned long wait,boolean restart)
{
    //is the time up for this task?
    if (millis() - lastMillis >= wait)
    {
        //should this start again?
        if(restart)
        {
            //get ready for the next iteration
            lastMillis = millis(); //get ready for the next iteration
        }
        return true;
    }
    return false;

} // END of CheckTime()

#endif //HTTPSECURE_CLOCK_SETUP_H
