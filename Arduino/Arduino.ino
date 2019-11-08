#include "esp_bt.h"
#include "esp_wifi.h"
#include "esp_sleep.h"
#include "WifiCredentials.h"
String type = "sensor";                  // Enter the type of your client here.
String subtype = "button";
#define clienttype button                // Enter the subtype of your client here.

#define debugmode true                   // true: some more debug information
//#define reset_authcode true               // true: resets authcode

int requesttimeout;

void setup() {

  Serial.begin(115200);
  esp_bt_controller_disable();

#if reset_authcode == true
  resetauthcode();
  while(1);
#endif
  
  wifisetup();

#if clienttype == button
  buttonsetup();
#elif clienttype == finger
  fingersetup();
#elif clienttype == temp
  tempsetup();
#elif clienttype == rotation
  rotationsetup();
#elif clienttype == rgb
  rgbsetup();
#elif clienttype == rgbledstrip
  rgbledstripsetup();
#elif clienttype == epaper
  epapersetup();
#elif clienttype == lock
  locksetup();
#elif clienttype == motor
  motorsetup();
#endif

}

void loop() {

#ifdef clienttype == button
  buttonloop();
#elif clienttype == finger
  fingerloop();
#elif clienttype == temp
  temploop();
#elif clienttype == rotation
  rotationloop();
#elif clienttype == rgb
  rgbloop();
#elif clienttype == rgbledstrip
  rgbledstriploop();
#elif clienttype == epaper
  epaperloop();
#elif clienttype == lock
  lockloop();
#elif clienttype == motor
  motorloop();
#endif
  
}
