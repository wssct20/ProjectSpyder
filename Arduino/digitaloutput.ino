
#define output_pin 5    //Enter the pin of your output here

void digitaloutputsetup() {

  digitalWrite(output_pin, LOW);
  
  jsonstructure = "{\
\"data\":{\
\"state\":0\
},\
\"usermodifiabledata\":[\"state\"],\
\"friendly\":{\
\"datavar\":{\
\"state\":\"Output State\"\
},\
\"datavalue\":{\
\"state\":\"off\"\
},\
\"type\":\"Digital Output\"\
},\
\"preferredupdatetime\":10\
}";
  
}

void digitaloutputloop() {

  #ifdef debugmode
    Serial.println("digitaloutputloop()");
  #endif
  
  String digitaloutputdata;

  //get data from system
  DynamicJsonDocument receiveddata(JSONCAPACITY);
  deserializeJson(receiveddata, getdata());

  uint8_t outputstate = receiveddata["data"]["state"].as<uint8_t>();

  if (outputstate != 1) outputstate = 0;

  DynamicJsonDocument datadoc(JSONCAPACITY);

  if (receiveddata["data"]["state"].as<String>() != String(outputstate)) {
    JsonObject data = datadoc.createNestedObject("data");
    data["state"] = outputstate;
  }

  #ifdef debugmode
    Serial.println("outputstate: " + String(outputstate));
  #endif

  //set output
  digitalWrite(output_pin, outputstate);

  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  const String friendlystate[] = {
    "off",
    "on",
  };
  datavalue["state"] = friendlystate[outputstate];

  serializeJson(datadoc, digitaloutputdata);
  
  //send the values to the server
  updatedata(digitaloutputdata);

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
