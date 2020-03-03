
#define buttonPin 4
//#define touchthreshold 40

const String friendlybuttonstate[] = {
  "Released",
  "Pressed",
};

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);

  jsonstructure = "{\"data\":{\"data\":{\"state\":0},\"friendly\":{\"datavar\":{\"state\":\"button state\"},\"datavalue\":{\"state\":\"Released\"},\"button\":\"Button\"},\"preferredupdatetime\":120}}";

}

void buttonloop() {

  String buttondata;
  
  DynamicJsonDocument datadoc(JSONCAPACITY);
  JsonObject data = datadoc.createNestedObject("data");
  JsonObject friendly = datadoc.createNestedObject("friedly");
  uint8_t buttonstate = !digitalRead(buttonPin);
  #ifdef debugmode
    Serial.println("buttonstate: " + String(buttonstate));
  #endif
  data["state"] = buttonstate;
  friendly["datavalue"] = friendlybuttonstate[buttonstate];
  serializeJson(datadoc, buttondata);
  #ifdef debugmode
    Serial.println("JSON: " + String(buttondata));
  #endif
  
//  bool buttonstate = lightsleepgpio(requesttimeout, buttonPin, 0); TODO: add gpiowakeup

  updatedata(buttondata);

  lightsleep(requesttimeout);
  
}
