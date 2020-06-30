
#define buttonPin 4   //Enter the pin of your button here
//#define touchthreshold 40

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);

  //set client specific jsonstructure
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
  
  //read data from server
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

  //send the values to the server
  updatedata(buttondata);

  //go to lightsleep + wake up if button is pressed
  lightsleepgpio(requesttimeout, buttonPin, 0);
  
}
