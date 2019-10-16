#include "WiFi.h"

#include "WifiCredentials"

const char * hostname = "SpyderClient";

void setup()
{
    Serial.begin(115200);
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

void loop()
{
    delay(1000);

    //Serial.println(WiFi.RSSI());

}
