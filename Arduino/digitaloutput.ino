
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
\"datavalues\":{\
\"state\":\"off\"\
},\
\"type\":\"Digital Output\"\
},\
\"preferredupdatetime\":10\
}";
  
}

void digitaloutputloop() {

  String digitaloutputdata;

  #ifdef debugmode
    Serial.println("digitaloutput() look for data");
  #endif

  //get data from system
  DynamicJsonDocument receiveddata(JSONCAPACITY);
  deserializeJson(receiveddata, getdata());

  int outputstate = receiveddata["data"]["state"].as<int>();

  //check data
  if (outputstate != 1) outputstate = 0;

  #ifdef debugmode
    Serial.println("outputstate: " + String(outputstate));
  #endif

  //set output
  digitalWrite(output_pin, outputstate);

  DynamicJsonDocument datadoc(JSONCAPACITY);
  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  const String friendlystate[] = {
    "off",
    "on",
  };
  datavalue["state"] = friendlystate[outputstate];

  serializeJson(datadoc, digitaloutputdata);

  #ifdef debugmode
    Serial.println("JSON: " + String(digitaloutputdata));
  #endif
  
  //send the values to the server
  updatedata(digitaloutputdata);

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
