//#include "esp_bt.h"
#include "esp_wifi.h"
#include "WifiCredentials.h"
#define clienttype rgbled                // Enter the type of your client here.
String type = "rgbled";                  // Enter the type of your client here.

#define debugmode true                   // true: some more debug information
//#define reset_authcode true              // true: resets authcode

int requesttimeout;

void setup() {

  Serial.begin(115200);
  //esp_bt_controller_disable(); //disable bluetooth controller for power savings, but currently commented out, because I believe its not started if library isnt included

  #if reset_authcode == true
    resetauthcode();
    Serial.println("authcode has been reset!");
    while(1);
  #endif
  
  wifisetup();

  #if (clienttype == button)
    buttonsetup();
  #elif (clienttype == finger)
    fingersetup();
  #elif (clienttype == temp)
    tempsetup();
  #elif (clienttype == rotation)
    rotationsetup();
  #elif (clienttype == rgb)
    rgbsetup();
  #elif (clienttype == addressablergbledstrip)
    addressablergbledstripsetup();
  #elif (clienttype == rgbled)
    rgbledsetup();
  #elif (clienttype == epaper)
    epapersetup();
  #elif (clienttype == lock)
    locksetup();
  #elif (clienttype == motor)
    motorsetup();
  #endif

}

void loop() {

  #if (clienttype == button)
    buttonloop();
  #elif clienttype == finger)
    fingerloop();
  #elif clienttype == temp
    temploop();
  #elif (clienttype == rotation)
    rotationloop();
  #elif (clienttype == rgb)
    rgbloop();
  #elif (clienttype == addressablergbledstrip)
    addressablergbledstripsetup();
  #elif (clienttype == rgbled)
    rgbledloop();
  #elif (clienttype == epaper)
    epaperloop();
  #elif (clienttype == lock)
    lockloop();
  #elif (clienttype == motor)
    motorloop();
  #endif
  
}
