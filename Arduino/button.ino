
#define buttonPin 4
//#define touchthreshold 40

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);

}

void buttonloop() {

  String buttondata;
  
  DynamicJsonDocument datadoc(JSONCAPACITY);
  JsonObject data = datadoc.createNestedObject("data");
  uint8_t buttonstate = !digitalRead(buttonPin);
  #ifdef debugmode
    Serial.println("buttonstate: " + String(buttonstate));
  #endif
  data["state"] = buttonstate;
  serializeJson(datadoc, buttondata);
  #ifdef debugmode
    Serial.println("JSON: " + String(buttondata));
  #endif
  
//  bool buttonstate = lightsleepgpio(requesttimeout, buttonPin, 0); TODO: add gpiowakeup

  updatedata(buttondata);

  lightsleep(requesttimeout);
  
}
