#include "RealTimeManager.h"

RealTimeManager::RealTimeManager(const char* ntpServer, int timeZoneOffset)
    : ntpServer(ntpServer), timeZoneOffset(timeZoneOffset),
      timeClient(ntpUDP, ntpServer, timeZoneOffset * 3600) {}

void RealTimeManager::begin() {
    timeClient.begin();
    timeClient.update(); // Synchronize time with NTP server
}

void RealTimeManager::update() {
    timeClient.update(); // Update the time from NTP server
}

String RealTimeManager::getCurrentDate() {
    unsigned long epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int year = ptm->tm_year + 1900;
    int month = ptm->tm_mon + 1;
    int day = ptm->tm_mday;
    return String(year) + "-" + String(month) + "-" + String(day);
}

String RealTimeManager::getCurrentTime() {
    return timeClient.getFormattedTime();
}

String RealTimeManager::getCurrentDateTime() {
    String currentDate = getCurrentDate();
    String currentTime = getCurrentTime();
    return currentDate + " " + currentTime;
}
