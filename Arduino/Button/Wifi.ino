#include "WiFi.h"
#include "WifiCredentials.h"

const char * hostname = "SpyderClient";

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
      delay(10000);
    }
    Serial.println();
    
    Serial.println("Wifi Connected");
    Serial.println(WiFi.getHostname());
}
