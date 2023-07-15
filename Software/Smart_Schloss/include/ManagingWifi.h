#ifndef MANAGINGWIFI_H
#define MANAGINGWIFI_H

#include <WiFi.h>

class ManagingWifi {
public:
  ManagingWifi();
  ManagingWifi(const char* ssid, const char* password);
  void connectToDifferentWifi(const char* ssid, const char* password); // To be used when wifi network should be changed
  void handleConnectionStatus();
  void disconnect();
  IPAddress getIPAddress();
  int getSignalStrength();
  void setIPAddress();
  void setSignalStrength();
  int getWifiStatus();
private:
    int previousStatus = -1;
    String _ssid; // Change to String object
    String _password; // Change to String object
    int _signalStrength;
    IPAddress _ipAddress;
};

#endif