
#define buttonPin 4
//#define touchthreshold 40

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);

  jsonstructure = "{\
\"data\":{\
\"state\":0\
},\
\"friendly\":{\
\"datavar\":{\
\"state\":\"button state\"\
},\
\"datavalue\":{\
\"state\":\"Released\"\
},\
\"type\":\"Button\"\
},\
\"preferredupdatetime\":120\
}";

}

void buttonloop() {

  String buttondata;
  
  DynamicJsonDocument datadoc(JSONCAPACITY);
  JsonObject data = datadoc.createNestedObject("data");
  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  uint8_t buttonstate = !digitalRead(buttonPin);
  //bool buttonstate = !lightsleepgpio(requesttimeout, buttonPin, 0);
  #ifdef debugmode
    Serial.println("buttonstate: " + String(buttonstate));
  #endif
  data["state"] = buttonstate;
  const String friendlybuttonstate[] = {
    "Released",
    "Pressed",
  };
  datavalue["state"] = friendlybuttonstate[buttonstate];
  serializeJson(datadoc, buttondata);
  #ifdef debugmode
    Serial.println("JSON: " + String(buttondata));
  #endif
  
//  bool buttonstate = lightsleepgpio(requesttimeout, buttonPin, 0); TODO: add gpiowakeup

  updatedata(buttondata);

  lightsleep(requesttimeout);
  
}
