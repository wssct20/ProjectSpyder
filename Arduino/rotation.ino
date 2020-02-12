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
  if (rotation.begin())
  {
    #ifdef debugmode
      Serial.println("Found rotation sensor");
    #endif
  }
  else
  {
    #ifdef debugmode
      Serial.println("No rotation sensor found");
    #endif
    hibernate(60*60*24);
  }

  rotation.setExtCrystalUse(true);
  
}

void rotationloop() {

  int8_t temp;                        //temperature
  uint16_t x, y, z, m, mx, my, mz;    //gyroskop and magnetometer values
  uint8_t sc, gc, ac, mc = 0;         //calibration values

  imu::Vector<3> euler = rotation.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> magnetic = rotation.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

//////////temperature//////////

  temp = rotation.getTemp();
  #ifdef debugmode
    Serial.println("Current temperature: " + String(temp));
  #endif

//////////gyroskop//////////

  x = (int) (euler.x() + 0.5);
  #ifdef debugmode
    Serial.println("x: " + String(x));
  #endif

  y = (int) (euler.y() + 0.5);
  #ifdef debugmode
    Serial.println("y: " + String(y));
  #endif

  z = (int) (euler.z() + 0.5);
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
  #ifdef debugmode
    Serial.println("m: " + String(m));
  #endif

//////////calibration//////////
  
  rotation.getCalibration(&sc, &gc, &ac, &mc);
  #ifdef debugmode
    Serial.println("system calibration: " + String(sc));
    Serial.println("magnet calibration: " + String(mc));
  #endif

  String state = String(temp);
  state.concat(":");
  state.concat(x);
  state.concat(":");
  state.concat(y);
  state.concat(":");
  state.concat(z);
  state.concat(":");
  state.concat(m);

  #ifdef debugmode
    Serial.println("state: " + String(state));
  #endif

  putstate(state);

  lightsleep(requesttimeout);
}
