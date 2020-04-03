
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
\"preferredupdatetime\":30\
}";

}

void buttonloop() {

  #ifdef debugmode
    Serial.println("buttonloop()");
  #endif

  String buttondata;
  
  DynamicJsonDocument datadoc(JSONCAPACITY);
  JsonObject data = datadoc.createNestedObject("data");
  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  bool buttonstate;
  esp_sleep_wakeup_cause_t wakeupreason = esp_sleep_get_wakeup_cause();
  if (wakeupreason == ESP_SLEEP_WAKEUP_GPIO) {
    buttonstate  = 1;
  }
  else {
    buttonstate = !digitalRead(buttonPin);
  }
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

  updatedata(buttondata);

  lightsleepgpio(requesttimeout, buttonPin, 0);
  
}
