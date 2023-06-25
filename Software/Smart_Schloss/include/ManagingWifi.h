#ifndef MANAGINGWIFI_H
#define MANAGINGWIFI_H

#include <WiFi.h>

class ManagingWifi {
public:
  ManagingWifi(const char* ssid, const char* password);
  void connectToDifferentWifi(const char* ssid, const char* password);
  void handleConnectionStatus();
  void disconnect();
  IPAddress getIPAddress();
  int getSignalStrength();
  void setIPAddress();
  void setSignalStrength();
  int getWifiStatus();
private:
    int previousStatus = -1;
    const char* _ssid;
    const char* _password;
    int _signalStrength;
    IPAddress _ipAddress;
};

#endif
