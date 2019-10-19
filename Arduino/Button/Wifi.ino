#include "WiFi.h"
#include "WifiCredentials.h"

const char * hostname = "SpyderClient";

byte mac[6];

void wifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname);

    Serial.print("Connecting...");
    
    WiFi.begin(ssid, password);
    delay(1000);
    
    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      WiFi.begin(ssid, password);
      delay(5000);
    }
    Serial.println();    
    Serial.print("Wifi Connected to \"");
    Serial.print(ssid);
    Serial.println("\"");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    Serial.print(mac[0],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.println(mac[5],HEX);
    Serial.print("Hostname: ");
    Serial.println(WiFi.getHostname());
    Serial.println("_________________________________");
}
