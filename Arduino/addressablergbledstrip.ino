#include <NeoPixelBrightnessBus.h>

#define datapin 5           //Pin to which the data pin of the strip is connected
#define ledcount 60*5       //Number of connected LEDs

//initialise the sensor
NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> ledstrip(ledcount, datapin); 

void addressablergbledstripsetup() {

  ledstrip.Begin();             //starts the connection to the led strip
  ledstrip.SetBrightness(50);   //sets the maximum brightness

  //puts a initialize state to the system
  String initstate = "";
  initstate.concat(ledcount);
  initstate.concat(":");
  for(int i = 0; i < ledcount; i++) {
    initstate.concat("000000");
  }
  putstate(initstate);
  
}

void addressablergbledstriploop() {

  #ifdef debugmode
    Serial.println("ledstrip look for state");
  #endif

  String rawstate = getstate();               //get state from system

  int statecount = rawstate.substring(0, rawstate.indexOf(":")).toInt();    //gets the count of leds
  String ledstate = rawstate.substring(rawstate.indexOf(":") + 1);          //gets the led states
  
  for(int i = 0; i < statecount; i++) {
    if(i >= ledcount) break;
    
    ledstate.substring(i * 6, (i + 1) * 6);     //extracts the state of a single led
    
    //extracts the rgb states of a single led
    uint8_t colors[3];
    for(int i = 0; i < 3; i++) {
      colors[i] = hextodec(ledstate.substring(i * 2, (i + 1) * 2));
    }
    
    ledstrip.SetPixelColor(i, RgbColor(colors[0], colors[1], colors[2]));   //sets the led state
  }

  ledstrip.Show();      //shows the states on the strip

  lightsleep(requesttimeout);
  
}
