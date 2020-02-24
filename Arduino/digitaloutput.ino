
#define output_pin 5    //Enter the pin of your output here

void digitaloutputsetup() {

  digitalWrite(output_pin, LOW);
  
  putstate("1");    //only a test state
  
}

void digitaloutputloop() {

  #ifdef debugmode
    Serial.println("digitaloutput() look for data");
  #endif

  //get data from system
  DynamicJsonDocument data(JSONCAPACITY);
  deserializeJson(data,getdata());

  int outputstate = data["data"]["state"].as<int>();

  //check data
  if (outputstate != 1) outputstate = 0;

  #ifdef debugmode
    Serial.println("outputstate: " + String(outputstate));
  #endif

  //set output
  digitalWrite(output_pin, outputstate);

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
