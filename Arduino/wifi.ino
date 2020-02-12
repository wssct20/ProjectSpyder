#include "WiFi.h"

//#define clienthostname "SpyderClient"
const char * clienthostname = "SpyderClient";

void wifisetup()
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(clienthostname);

    #ifdef debugmode
      Serial.print("Connecting...");
    #endif
    
    WiFi.begin(ssid, password);
    delay(1000);
    
    while(WiFi.status() != WL_CONNECTED){
      #ifdef debugmode
        Serial.print(".");
      #endif
      WiFi.begin(ssid, password);
      delay(5000);
    }
    #ifdef debugmode
      Serial.println();    
      Serial.println("Wifi Connected to \"" + String(ssid) + String("\""));     // Wifi connection
      Serial.println("IP address: " + String(WiFi.localIP()));                  // IP address
      byte mac[6];                                                              // MAC address
      WiFi.macAddress(mac);
      Serial.println("MAC address: " + String(mac[0],HEX) + String(":") + String(mac[1],HEX) + String(":") + String(mac[2],HEX) + String(":") + String(mac[3],HEX) + String(":") + String(mac[4],HEX) + String(":") + String(mac[5],HEX));
      Serial.println("Hostname: " + String(WiFi.getHostname()));                // Hostname
      Serial.println("_________________________________");
    #endif
}
