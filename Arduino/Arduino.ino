#include "WifiCredentials.h"
#define button                // Enter the type of your client here.


void setup() {

  Serial.begin(115200);
  
  wifisetup();

#ifdef button
  buttonsetup();
#elif defined finger
  fingersetup();
#elif defined temp
  tempsetup();
#elif defined rotation
  rotationsetup();
#elif defined rgb
  rgbsetup();
#elif defined rgbledstrip
  rgbledstripsetup();
#elif defined epaper
  epapersetup();
#elif defined lock
  locksetup();
#elif defined motor
  motorsetup();
#endif

}

void loop() {

  phprequest();

#ifdef button
  buttonloop();
#elif defined finger
  fingerloop();
#elif defined temp
  temploop();
#elif defined rotation
  rotationloop();
#elif defined rgb
  rgbloop();
#elif defined rgbledstrip
  rgbledstriploop();
#elif defined epaper
  epaperloop();
#elif defined lock
  lockloop();
#elif defined motor
  motorloop();
#endif
  
}
