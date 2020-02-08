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
    Serial.println("Found rotation sensor");
  }
  else
  {
    Serial.println("No rotation sensor found");
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
  Serial.println("Current temperature: " + String(temp));

//////////gyroskop//////////

  x = (int) (euler.x() + 0.5);
  Serial.println("x: " + String(x));

  y = (int) (euler.y() + 0.5);
  Serial.println("y: " + String(y));

  z = (int) (euler.z() + 0.5);
  Serial.println("z: " + String(z));

//////////magnetometer//////////

  mx = (int) (magnetic.x() + 0.5);
  Serial.println("mx: " + String(mx));
  
  my = (int) (magnetic.y() + 0.5);
  Serial.println("my: " + String(my));
  
  mz = (int) (magnetic.z() + 0.5);
  Serial.println("mz: " + String(mz));

  m = max(mx, max(my, mz));
  Serial.println("m: " + String(m));

//////////calibration//////////
  
  rotation.getCalibration(&sc, &gc, &ac, &mc);
  Serial.println("system calibration: " + String(sc));
  Serial.println("magnet calibration: " + String(mc));

  String state = String(temp);
  state.concat(":");
  state.concat(x);
  state.concat(":");
  state.concat(y);
  state.concat(":");
  state.concat(z);
  state.concat(":");
  state.concat(m);

  Serial.println("state: " + String(state));

  putstate(state);

  lightsleep(requesttimeout);
}
