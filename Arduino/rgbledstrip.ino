/*#include <Adafruit_NeoPixel.h>

#define datapin 5         //Pin to which the data pin of the strip is connected
#define lednumber 60      //Number of connected LEDs

Adafruit_NeoPixel ledstrip(lednumber, datapin, NEO_GRB + NEO_KHZ800);

void rgbledstripsetup() {

  ledstrip.begin();
  ledstrip.clear();
  
}

void rgbledstriploop() {

  for (int i = 0; i < lednumber; i++)
  {
    ledstrip.setPixelColor(i, ledstrip.Color(0, 150, 0));

    ledstrip.show();

    delay(500);
  }
  
}*/
