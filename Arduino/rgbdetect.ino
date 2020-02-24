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
  
}

void rgbdetectloop() {

  uint16_t r, g, b, c, colortemp, lux;

  //turn on the sensor led
  digitalWrite(detectledpin, HIGH);
  delay(250);

  //measure the rgb values and calculate the themperature and brightness
  rgbdetect.getRawData(&r, &g, &b, &c);
  colortemp = rgbdetect.calculateColorTemperature_dn40(r, g, b, c);
  lux = rgbdetect.calculateLux(r, g, b);

  //turn off the sensor led
  digitalWrite(detectledpin, LOW);

  #ifdef debugmode
    Serial.print("Color Temp: "); Serial.print(colortemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
  #endif

  String state = String(r);
  state.concat(":");
  state.concat(g);
  state.concat(":");
  state.concat(b);
  state.concat(":");
  state.concat(c);
  state.concat(":");
  state.concat(colortemp);
  state.concat(":");
  state.concat(lux);

  #ifdef debugmode
    Serial.println("state: " + String(state));
  #endif
  
  //send the values to the server
  putstate(state);

  lightsleep(requesttimeout);
  
}
