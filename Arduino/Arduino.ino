
//#include "esp_bt.h"
#include "esp_wifi.h"
#include "WifiCredentials.h"
const String type = "rgbled";            // Enter the type of your client here.

#define debugmode true                   // true: some more debug information
//#define reset_authcode true              // true: resets authcode

int requesttimeout;

//typesstring: defines supported types, new type every 25 chars, used for switch in setup() and loop()
#define typesstringtypelength 25
const String typesstring = "button                   finger                   temp                     rotation                 rgb                      addressablergbledstrip   rgbled                   epaper                   lock                     motor                    ";    // type every 25 chars
String switchtype = type;

void setup() {

  Serial.begin(115200);
  //esp_bt_controller_disable(); //disable bluetooth controller for power savings, but currently commented out, because I believe its not started if library isnt included

  #if reset_authcode == true
    resetauthcode();
    Serial.println("authcode has been reset!");
    while(1);
  #endif
  
  {
    //fill up switchtype with spaces up to typesstringtypelength chars for switch to work properly
    int length = switchtype.length();
    if (length > typesstringtypelength) switchtype = switchtype.substring(0, typesstringtypelength);
    for (int i = length; i < typesstringtypelength; i++) {
      switchtype.concat(" ");
    }
  }

  Serial.print("switchtype: ");
  Serial.print(switchtype);
  Serial.println(".");
  
  wifisetup();
  
  int e = typesstring.indexOf(switchtype);
  if (e == -1)
  {
    Serial.println("Current type invalid.");
    hibernate(60*60*24);
  }
  switch (e / typesstringtypelength)
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

  Serial.println("setup finished");

}

void loop() {

  int e = typesstring.indexOf(switchtype);
  if (e == -1)
  {
    Serial.println("Current type invalid.");
    hibernate(60*60*24);
  }
  switch (e / typesstringtypelength)
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
