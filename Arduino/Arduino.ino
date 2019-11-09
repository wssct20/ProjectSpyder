//#include "esp_bt.h"
#include "esp_wifi.h"
#include "WifiCredentials.h"
String type = "rgbled";                  // Enter the type of your client here.

#define debugmode true                   // true: some more debug information
//#define reset_authcode true              // true: resets authcode

int requesttimeout;

//typesstring: defines supported types, new type every 25 chars, used for switch in setup() and loop()
String typesstring = "button                  finger                  temp                    rotation                rgb                     addressablergbledstrips rgbled                  epaper                  lock                    motor                   ";    // type every 25 chars

void setup() {

  Serial.begin(115200);
  //esp_bt_controller_disable(); //disable bluetooth controller for power savings, but currently commented out, because I believe its not started if library isnt included

  #if reset_authcode == true
    resetauthcode();
    Serial.println("authcode has been reset!");
    while(1);
  #endif
  
  wifisetup();
  
  
  
  int e = typesstring.indexOf(type);
  if (e == -1)
  {
    Serial.println("Current type invalid.");
    hibernate(60*60*24);
  }
  switch (e / 25)
  {
    case 0:
      buttonsetup();
      break;
    case 1:
      //fingersetup();
      break;
    case 2:
      //tempsetup();
      break;
    case 3:
      //rotationsetup();
      break;
    case 4:
      rgbsetup();
      break;
    case 5:
      //addressablergbledstripsetup();
      break;
    case 6:
      rgbledsetup();
      break;
    case 7:
      //epapersetup();
      break;
    case 8:
      //locksetup();
      break;
    case 9:
      //motorsetup();
      break;
    default:
      Serial.println("Current type invalid.");
      hibernate(60*60*24);
  }

}

void loop() {

  int e = typesstring.indexOf(type);
  if (e == -1)
  {
    Serial.println("Current type invalid.");
    hibernate(60*60*24);
  }
  switch (e / 25)
  {
    case 0:
        buttonloop();
        break;
    case 1:
        //fingerloop();
        break;
    case 2:
        //temploop();
        break;
    case 3:
        //rotationloop();
        break;
    case 4:
        rgbloop();
        break;
    case 5:
        //addressablergbledstripsetup();
        break;
    case 6:
        rgbledloop();
        break;
    case 7:
        //epaperloop();
        break;
    case 8:
        //lockloop();
        break;
    case 9:
        //motorloop();
        break;
    default:
      Serial.println("Current type invalid.");
      hibernate(60*60*24);
  }
  
}
