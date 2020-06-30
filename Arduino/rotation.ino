#include "Adafruit_BNO055.h"

/*
 * Connection:
 * VDD  to 3.3V-5V DC
 * GND  to GND (common ground)
 * SCL  to the I²C SCL (at the ESP32 GPIO 22)
 * SDA  to the I²C SDA (at the ESP32 GPIO 21)
 */

//initialise the sensor
Adafruit_BNO055 rotation = Adafruit_BNO055(-1, 0x28);

void rotationsetup() {

  //start the sensor communication
  if (rotation.begin()) {
    #ifdef debugmode
      Serial.println("Found rotation sensor");
    #endif
  }
  else {
    Serial.println("ERROR: No rotation sensor found");
    hibernate(60*60*24);
  }

  rotation.setExtCrystalUse(true);

  //set client specific jsonstructure
  jsonstructure = "{\
\"settings\":{\
\"resetreferenceposition\":0\
},\
\"data\":{\
\"temperature\":0,\
\"x-rotation\":0,\
\"y-rotation\":0,\
\"z-rotation\":0,\
\"magnetvalue\":0\
},\
\"friendly\":{\
\"settingsvar\":{\
\"resetreferenceposition\":\"Reset reference position\"\
},\
\"datavar\":{\
\"temperature\":\"Temperature\",\
\"x-rotation\":\"x-Rotation\",\
\"y-rotation\":\"y-Rotation\",\
\"z-rotation\":\"z-Rotation\",\
\"magnetvalue\":\"Magnetvalue\"\
},\
\"datavalue\":{\
\"temperature\":\"0°C\",\
\"x-rotation\":\"0°\",\
\"y-rotation\":\"0°\",\
\"z-rotation\":\"0°\",\
\"magnetvalue\":\"0µT\"\
},\
\"type\":\"Rotation Sensor\"},\
\"preferredupdatetime\":5\
}";
  
}

void rotationloop() {

  String rotationdata;

  //get data from system
  DynamicJsonDocument receiveddata(JSONCAPACITY);
  deserializeJson(receiveddata, getdata());

  DynamicJsonDocument datadoc(JSONCAPACITY);
  JsonObject settings = datadoc.createNestedObject("settings");

  bool resetreferenceposition = receiveddata["settings"]["resetreferenceposition"];

  if (resetreferenceposition != true) {
    resetreferenceposition = false;
    settings["resetreferenceposition"] = false;
  }

  else {
    //TODO: add resetreferenceposition
    settings["resetreferenceposition"] = false;
  }

  int8_t temp;                        //temperature
  uint16_t x, y, z, m, mx, my, mz;    //gyroskop and magnetometer values
  uint8_t sc, gc, ac, mc = 0;         //calibration values

  imu::Vector<3> euler = rotation.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> magnetic = rotation.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

  JsonObject data = datadoc.createNestedObject("data");

//////////temperature//////////

  temp = rotation.getTemp();
  data["temperature"] = temp;
  #ifdef debugmode
    Serial.println("Current temperature: " + String(temp));
  #endif

//////////location//////////

  x = (int) (euler.x() + 0.5);
  data["x-rotation"] = x;
  #ifdef debugmode
    Serial.println("x: " + String(x));
  #endif

  y = (int) (euler.y() + 0.5);
  data["y-rotation"] = y;
  #ifdef debugmode
    Serial.println("y: " + String(y));
  #endif

  z = (int) (euler.z() + 0.5);
  data["z-rotation"] = z;
  #ifdef debugmode
    Serial.println("z: " + String(z));
  #endif

//////////magnetometer//////////

  mx = (int) (magnetic.x() + 0.5);
  #ifdef debugmode
    Serial.println("mx: " + String(mx));
  #endif
  
  my = (int) (magnetic.y() + 0.5);
  #ifdef debugmode
    Serial.println("my: " + String(my));
  #endif
  
  mz = (int) (magnetic.z() + 0.5);
  #ifdef debugmode
    Serial.println("mz: " + String(mz));
  #endif

  m = max(mx, max(my, mz));
  data["magnetvalue"] = m;
  #ifdef debugmode
    Serial.println("m: " + String(m));
  #endif

//////////calibration//////////
  
  rotation.getCalibration(&sc, &gc, &ac, &mc);
  #ifdef debugmode
    Serial.println("system calibration: " + String(sc));
    Serial.println("magnet calibration: " + String(mc));
  #endif

  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  String friendlytemp = String(temp);
  friendlytemp.concat("°C");
  datavalue["temperature"] = friendlytemp;
  String friendlyx = String(x);
  friendlyx.concat("°");
  datavalue["x-rotation"] = friendlyx;
  String friendlyy = String(y);
  friendlyy.concat("°");
  datavalue["y-rotation"] = friendlyy;
  String friendlyz = String(z);
  friendlyz.concat("°");
  datavalue["z-rotation"] = friendlyz;
  String friendlym = String(m);
  friendlym.concat("µT");
  datavalue["magnetvalue"] = friendlym;

  serializeJson(datadoc, rotationdata);

  //send the values to the server
  updatedata(rotationdata);

  //go to lightsleep
  lightsleep(requesttimeout);
}
