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
int detectledpin = 23;

void rgbdetectsetup() {

  //start the sensor communication
  if (rgbdetect.begin()) {
    #ifdef debugmode
      Serial.println("Found rgb sensor");
    #endif
  }
  else {
    #ifdef debugmode
      Serial.println("No rgb sensor found");
    #endif
    hibernate(60*60*24);
  }

  //initialise the sensor led
  pinMode(detectledpin, OUTPUT);
  digitalWrite(detectledpin, LOW);

  jsonstructure = "{\
\"data\":{\
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
\"rgbdetect\":\"Color Sensor\"\
},\
\"preferredupdatetime\":20\
}\
}";
  
}

void rgbdetectloop() {

  String rgbdetectdata;
  
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

  //measure the rgb values and calculate the themperature and brightness
  rgbdetect.getRawData(&r, &g, &b, &c);
  colortemp = rgbdetect.calculateColorTemperature_dn40(r, g, b, c);
  lux = rgbdetect.calculateLux(r, g, b);

  if (ledstate != 1) {
    //turn off the sensor led
    digitalWrite(detectledpin, LOW);
  }

  #ifdef debugmode
    Serial.print("Color Temp: "); Serial.print(colortemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
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

  #ifdef debugmode
    Serial.println("JSON: " + String(rgbdetectdata));
  #endif
  
  //send the values to the server
  updatedata(rgbdetectdata);

  lightsleep(requesttimeout);
  
}
