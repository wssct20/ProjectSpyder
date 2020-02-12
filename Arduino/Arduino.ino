//#include "esp_bt.h"
#include "esp_wifi.h"
#include "WifiCredentials.h"
const String type = "temperature";      //Enter the type of your client here.

#define debugmode               //some more debug information
//#define reset_authcode          //resets authcode

int requesttimeout;

//typesstring: defines supported types, new type every 25 chars, used for switch in setup() and loop()
#define typesstringtypelength 25
const String typesstring = "button                   fingerprint              temperature              rotation                 rgbdetect                addressablergbledstrip   rgbled                   epaper                   digitaloutput            motor                    led                      ";    // type every 25 chars
String switchtype = type;

/*
 * Notes:
 * Currently EEPROM address 0-128 are used by the php script. Please stick to addresses after 128.
 */

void setup() {

  #ifdef debugmode
    Serial.begin(115200);
  #endif
  
  //esp_bt_controller_disable(); //disable bluetooth controller for power savings, but currently commented out, because I believe its not started if library isnt included

  #ifdef reset_authcode
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
  
  wifisetup();
  
  int e = typesstring.indexOf(switchtype);
  if (e == -1)
  {
    #ifdef debugmode
      Serial.println("Current type invalid.");
    #endif
    hibernate(60*60*24);
  }
  switch (e / typesstringtypelength)
  {
    case 0:
      buttonsetup();
      break;
    case 1:
      fingerprintsetup();
      break;
    case 2:
      temperaturesetup();
      break;
    case 3:
      rotationsetup();
      break;
    case 4:
      rgbdetectsetup();
      break;
    case 5:
      addressablergbledstripsetup();
      break;
    case 6:
      rgbledsetup();
      break;
    case 7:
      //epapersetup();
      break;
    case 8:
      digitaloutputsetup();
      break;
    case 9:
      //motorsetup();
      break;
    case 10:
      ledsetup();
      break;
    default:
      #ifdef debugmode
        Serial.println("Current type invalid.");
      #endif
      hibernate(60*60*24);
  }

}

void loop() {

  int e = typesstring.indexOf(switchtype);
  if (e == -1)
  {
    #ifdef debugmode
      Serial.println("Current type invalid.");
    #endif
    hibernate(60*60*24);
  }
  switch (e / typesstringtypelength)
  {
    case 0:
        buttonloop();
        break;
    case 1:
        fingerprintloop();
        break;
    case 2:
        temperatureloop();
        break;
    case 3:
        rotationloop();
        break;
    case 4:
        rgbdetectloop();
        break;
    case 5:
        addressablergbledstriploop();
        break;
    case 6:
        rgbledloop();
        break;
    case 7:
        //epaperloop();
        break;
    case 8:
        digitaloutputloop();
        break;
    case 9:
        //motorloop();
        break;
    case 10:
      ledloop();
      break;
    default:
      #ifdef debugmode
        Serial.println("Current type invalid.");
      #endif
      hibernate(60*60*24);
  }
  
}
