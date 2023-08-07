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
    Serial.println("Converting String to Time");

    int year, month, day, hour, minute, second;
    if (sscanf(datetimeString.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
        Serial.println("Parsing successful");

        struct tm tmTime;
        tmTime.tm_year = year - 1900;
        tmTime.tm_mon = month - 1;
        tmTime.tm_mday = day;
        tmTime.tm_hour = hour;
        tmTime.tm_min = minute;
        tmTime.tm_sec = second;
        time_t convertedTime = mktime(&tmTime);
        Serial.println("Conversion to time_t successful");
        return convertedTime;
    } else {
        Serial.println("Failed to parse datetime string");
        return -1;
    }
}