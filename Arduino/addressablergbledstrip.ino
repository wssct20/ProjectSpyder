#include <NeoPixelBrightnessBus.h>

#define datapin 5           //Pin to which the data pin of the strip is connected
#define ledcount 60*5       //Number of connected LEDs

//initialise the sensor
NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> ledstrip(ledcount, datapin); 

void addressablergbledstripsetup() {

  ledstrip.Begin();             //starts the connection to the led strip
  ledstrip.SetBrightness(50);   //sets the maximum brightness

  //set client specific jsonstructure
  jsonstructure = "{\
\"settings\":{\
\"mode\":0,\
\"brightness\":50\
},\
\"data\":{\
\"red\":0,\
\"green\":0,\
\"blue\":0\
},\
\"usermodifiabledata\":[\"red\",\"green\",\"blue\"],\
\"friendly\":{\
\"settingsvar\":{\
\"mode\":\"Mode\",\
\"brightness\":\"Brightness\"\
},\
\"datavar\":{\
\"red\":\"Red\",\
\"green\":\"Green\",\
\"blue\":\"Blue\"\
},\
\"type\":\"Addressable RGB-LED Strip\"\
},\
\"preferredupdatetime\":10\
}";
  
}

void addressablergbledstriploop() {

  #ifdef debugmode
    Serial.println("addressablergbledstriploop()");
  #endif
  
  String addressablergbledstripdata;

  //read data from server
  DynamicJsonDocument data(JSONCAPACITY);
  deserializeJson(data, getdata());

  ledstrip.SetBrightness(data["settings"]["brightness"].as<uint8_t>());
  
  uint8_t mode = data["settings"]["mode"].as<uint8_t>();
  #ifdef debugmode
    Serial.println("mode: " + String(mode));
  #endif
  switch (mode) {
    case 0: //values sent by the server
      {
        //read data
        int color[] = {
          data["data"]["red"].as<uint8_t>(),
          data["data"]["green"].as<uint8_t>(),
          data["data"]["blue"].as<uint8_t>(),
        };
        for (int i = 0; i < ledcount; i++) {
          ledstrip.SetPixelColor(i, RgbColor(color[0], color[1], color[2]));  //set the led state
        }
        ledstrip.Show();
      }
      break;
    /*case 1:
      //TODO: add non-blocking animation
      break;
    case 2:
      //TODO: add non-blocking animation
      break;*/
    default:
      {
        //switch all leds off
        for (int i = 0; i < ledcount; i++) {
          ledstrip.SetPixelColor(i, RgbColor(0, 0, 0));
        }
        ledstrip.Show();
      }
      break;
  }

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
