#include "RealTimeManager.h"
#include <ctime>

RealTimeManager::RealTimeManager(const char* ntpServer, int timeZoneOffset)
    : ntpServer(ntpServer), timeZoneOffset(timeZoneOffset),
      timeClient(ntpUDP, ntpServer, timeZoneOffset * 3600) {}

void RealTimeManager::begin() {
    timeClient.begin();
    timeClient.update(); // Synchronize time with NTP server
    Serial.println("Realtime server started.");
}

void RealTimeManager::update() {
    timeClient.update(); // Update the time from NTP server
}

String RealTimeManager::getCurrentDate() {
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = localtime(&epochTime); // Use localtime to get local time

    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
    return String(buffer);
}

String RealTimeManager::getCurrentTime() {
    return timeClient.getFormattedTime();
}

String RealTimeManager::getCurrentDateTime() {
    String currentDate = getCurrentDate();
    String currentTime = getCurrentTime();
    return currentDate + " " + currentTime;
}

time_t RealTimeManager::convertStringToTime(const String& datetimeString) {
    struct tm tmTime;
    strptime(datetimeString.c_str(), "%Y-%m-%d %H:%M:%S", &tmTime);
    return mktime(&tmTime);
}
