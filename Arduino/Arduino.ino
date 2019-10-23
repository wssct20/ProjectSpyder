#include "WifiCredentials.h"
String subtype = "button";

void setup() {

  wifisetup();
  switch(type) {
    case "button":
      buttonsetup();
      break;
    case "led":
      ledsetup();
      break;
    default:
      break;
  }
}

void loop() {

  phprequest();
  //clientloop();
}
