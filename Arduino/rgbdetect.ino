#include "Adafruit_TCS34725.h"

/*
 * Connection:
 * VDD  to 3.3V-5V DC
 * GND  to GND (common ground)
 * SCL  to the I²C SCL (at the ESP32 GPIO 22)
 * SDA  to the I²C SDA (at the ESP32 GPIO 21)
 */

//initialise the sensor
Adafruit_TCS34725 rgbdetect = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

//define the sensor led pin
#define detectledpin 23

void rgbdetectsetup() {

  //start the sensor communication
  if (rgbdetect.begin()) {
    #ifdef debugmode
      Serial.println("Found rgb sensor");
    #endif
  }
  else {
    Serial.println("ERROR: No rgb sensor found");
    hibernate(60*60*24);
  }

  //initialise the sensor led
  pinMode(detectledpin, OUTPUT);
  digitalWrite(detectledpin, LOW);

  //set client specific jsonstructure
  jsonstructure = "{\
\"data\":{\
\"red\":0,\
\"green\":0,\
\"blue\":0,\
\"clear\":0,\
\"colortemp\":0,\
\"brightness\":0,\
\"led\":0\
},\
\"usermodifiabledata\":[\"led\"],\
\"friendly\":{\
\"datavar\":{\
\"red\":\"Red\",\
\"green\":\"Green\",\
\"blue\":\"Blue\",\
\"clear\":\"White\",\
\"colortemp\":\"Color Temperature\",\
\"brightness\":\"Brightness\",\
\"led\":\"Lighting\"\
},\
\"datavalue\":{\
\"colortemp\":\"0 K\",\
\"brightness\":\"0 lx\",\
\"led\":\"off\"\
},\
\"type\":\"Color Sensor\"\
},\
\"preferredupdatetime\":10\
}";
  
}

void rgbdetectloop() {

  #ifdef debugmode
    Serial.println("rgbdetectloop()");
  #endif

  String rgbdetectdata;
  
  //get data from system
  DynamicJsonDocument receiveddata(JSONCAPACITY);
  deserializeJson(receiveddata, getdata());

  uint8_t ledstate = receiveddata["data"]["led"].as<uint8_t>();
  if (ledstate > 2) ledstate = 0;
  if (ledstate == 0) {
    //turn off the sensor led
    digitalWrite(detectledpin, LOW);
    delay(250);
  }
  else {
    //turn on the sensor led
    digitalWrite(detectledpin, HIGH);
    delay(250);
  }
  
  uint16_t r, g, b, c, colortemp, lux;
  DynamicJsonDocument datadoc(JSONCAPACITY);

  //measure the rgb values and calculate the temperature and brightness
  rgbdetect.getRawData(&r, &g, &b, &c);
  colortemp = rgbdetect.calculateColorTemperature_dn40(r, g, b, c);
  lux = rgbdetect.calculateLux(r, g, b);

  if (ledstate != 1) {
    //turn off the sensor led
    digitalWrite(detectledpin, LOW);
  }

  #ifdef debugmode
    Serial.println("Color Temp: " + String(colortemp, DEC) + String(" K"));
    Serial.println("Illuminance: " + String(lux, DEC) + String(" lux"));
    Serial.println("R: " + String(r, DEC));
    Serial.println("G: " + String(g, DEC));
    Serial.println("B: " + String(b, DEC));
    Serial.println("C: " + String(c, DEC));
  #endif

  JsonObject data = datadoc.createNestedObject("data");
  data["red"] = r;
  data["green"] = g;
  data["blue"] = b;
  data["clear"] = c;
  data["colortemp"] = colortemp;
  data["brightness"] = lux;
  data["led"] = ledstate;

  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  String friendlycolortemp = String(colortemp);
  friendlycolortemp.concat("K");
  String friendlybrightness = String(lux);
  friendlybrightness.concat("lx");
  datavalue["colortemp"] = friendlycolortemp;
  datavalue["brightness"] = friendlybrightness;
  const String friendlyled[] = {
    "off",
    "on",
    "auto",
  };
  datavalue["led"] = friendlyled[ledstate];

  serializeJson(datadoc, rgbdetectdata);
  
  //send the values to the server
  updatedata(rgbdetectdata);

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
