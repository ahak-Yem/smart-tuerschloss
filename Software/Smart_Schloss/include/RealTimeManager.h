#ifndef REALTIMEMANAGER_H
#define REALTIMEMANAGER_H

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class RealTimeManager {
private:
    const char* ntpServer;
    const int timeZoneOffset;
    WiFiUDP ntpUDP;
    NTPClient timeClient;

public:
    RealTimeManager(const char* ntpServer, int timeZoneOffset);
    void begin();
    void update();
    String getCurrentDate();
    String getCurrentTime();
    String getCurrentDateTime(); // New function to get date and time together
};

#endif
