#include <Adafruit_NeoPixel.h>

#define datapin 5           //Pin to which the data pin of the strip is connected
#define lednumber 60*5      //Number of connected LEDs

Adafruit_NeoPixel ledstrip(lednumber, datapin, NEO_GRB + NEO_KHZ800);

void addressablergbledstripsetup() {

  ledstrip.begin();
  ledstrip.show();
  ledstrip.setBrightness(50);
  
}

void addressablergbledstriploop() {

  Serial.println("3");

  for (int i = 0; i < lednumber; i++)
  {
    ledstrip.setPixelColor(i, ledstrip.Color(255, 0, 255));

    ledstrip.show();

    delay(100);
  }
  
}
