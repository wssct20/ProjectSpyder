#include "WiFi.h"

//#define clienthostname "SpyderClient"
const char * clienthostname = "SpyderClient";

void wifisetup() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(clienthostname);

  #ifdef debugmode
    Serial.print("Connecting...");
  #endif
  
  WiFi.begin(ssid, password);
  delay(1000);
  
  while(WiFi.status() != WL_CONNECTED) {
    #ifdef debugmode
      Serial.print(".");
    #endif
    WiFi.begin(ssid, password);
    delay(5000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    #ifdef debugmode
      Serial.println();
    #endif
      Serial.println("Wifi Connected to \"" + String(ssid) + String("\""));     // Wifi connection
    #ifdef debugmode
      Serial.println("IP address: " + String(WiFi.localIP()));                  // IP address
      byte mac[6];                                                              // MAC address
      WiFi.macAddress(mac);
      Serial.println("MAC address: " + String(mac[0], HEX) + String(":") + String(mac[1], HEX) + String(":") + String(mac[2], HEX) + String(":") + String(mac[3], HEX) + String(":") + String(mac[4], HEX) + String(":") + String(mac[5], HEX));
      Serial.println("Hostname: " + String(WiFi.getHostname()));                // Hostname
      Serial.println("_________________________________");
    #endif
  }
  else {
    Serial.print("ERROR: WiFi Connection failed: ");
    switch (WiFi.status()) {
      case WL_CONNECTED:
        Serial.print("WL_CONNECTED");
        break;
      case WL_NO_SHIELD:
        Serial.print("WL_NO_SHIELD");
        break;
      case WL_IDLE_STATUS:
        Serial.print("WL_IDLE_STATUS");
        break;
      case WL_NO_SSID_AVAIL:
        Serial.print("WL_NO_SSID_AVAIL");
        break;
      case WL_SCAN_COMPLETED:
        Serial.print("WL_SCAN_COMPLETED");
        break;
      case WL_CONNECT_FAILED:
        Serial.print("WL_CONNECT_FAILED");
        break;
      case WL_CONNECTION_LOST:
        Serial.print("WL_CONNECTION_LOST");
        break;
      case WL_DISCONNECTED:
        Serial.print("WL_DISCONNECTED");
        break;
      default:
        Serial.print("unknown(" + String(WiFi.status()) + ")");
        break;
    }
    Serial.println();
  }
}
