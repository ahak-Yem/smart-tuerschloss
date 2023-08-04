#ifndef REALTIMEMANAGER_H
#define REALTIMEMANAGER_H

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class RealTimeManager {
private:
    const char* ntpServer;
    int timeZoneOffset; // Changed from const to variable to adjust for daylight saving time
    WiFiUDP ntpUDP;
    NTPClient timeClient;

public:
    RealTimeManager(const char* ntpServer, int timeZoneOffset);
    void begin();
    void update();
    String getCurrentDate();
    String getCurrentTime();
    String getCurrentDateTime();
    time_t convertStringToTime(const String& datetimeString);
};

#endif