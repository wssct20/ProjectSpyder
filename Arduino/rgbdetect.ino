//#include "Wire.h"
#include "Adafruit_TCS34725.h"

/*
 * Connection:
 * VDD  to 3.3V-5V DC
 * GND  to GND (common ground)
 * SCL  to the I²C SCL (at the ESP32 GPIO 22)
 * SDA  to the I²C SDA (at the ESP32 GPIO 21)
 */

//Initialise the sensor
Adafruit_TXS34725 rgbdetect = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void rgbdetectsetup() {

  if (rgbdetect.begin())
  {
    Serial.println("Found rgb sensor");
  }
  else
  {
    Serial.println("No rgb sensor found");
    hibernate(60*60*24);
  }
  
}

void rgbdetectloop() {

  uint16_t r, g, b, c, colorTemp, lux;

  rgbdetect.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = rgbdetect.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  String state = r.concat(":")
    .concat(g).concat(":")
    .concat(b).concat(":")
    .concat(c).concat(":")
    .concat(colorTemp).concat(":")
    .concat(lux);

  Serial.println(state);
  putstate(state);

  lightsleep(requesttimeout);
  
}
