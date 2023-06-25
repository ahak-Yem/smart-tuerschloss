#include "ManagingWifi.h"

ManagingWifi::ManagingWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  _ssid = ssid;
  _password = password;
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
}

void ManagingWifi::disconnect() {
  WiFi.disconnect();
}

int ManagingWifi::getWifiStatus(){
  return previousStatus;
}

IPAddress ManagingWifi::getIPAddress() {
  return _ipAddress;
}

int ManagingWifi::getSignalStrength() {
  return _signalStrength;
}

void ManagingWifi::setIPAddress() {
  _ipAddress= WiFi.localIP();
}

void ManagingWifi::setSignalStrength() {
  _signalStrength=WiFi.RSSI();
}

void ManagingWifi::handleConnectionStatus() {
  int currentStatus = WiFi.status();
  
  if (currentStatus != previousStatus) {
    previousStatus = currentStatus;
    //To show on our platform and maybe log in DB.
    switch (currentStatus) {
      case WL_IDLE_STATUS:
        Serial.println("Status: Not connected to any network.");
        break;
      case WL_NO_SSID_AVAIL:
        Serial.println("Status: No WiFi networks were found.");
        break;
      case WL_SCAN_COMPLETED:
        Serial.println("Status: Scan for WiFi networks is completed.");
        break;
      case WL_CONNECTED:
        Serial.println("Status: Successfully connected to a WiFi network.");
        Serial.print("IP_Address: ");
        Serial.println(WiFi.localIP());
        break;
      case WL_CONNECT_FAILED:
        Serial.println("Status: Failed to connect to a WiFi network.");
        break;
      case WL_CONNECTION_LOST:
        Serial.println("Status: Connection to the WiFi network was lost.");
        break;
      case WL_DISCONNECTED:
        Serial.println("Status: Disconnected from the WiFi network.");
        break;
    }
  }
}
