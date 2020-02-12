
#define output_pin 5

void digitaloutputsetup() {

  digitalWrite(output_pin, LOW);
  
  putstate("1");    //only a test state
  
}

void digitaloutputloop() {

  #ifdef debugmode
    Serial.println("digitaloutput() look for state");
  #endif

  //get state from system
  String rawstate = getstate();
  #ifdef debugmode
    Serial.println("rawstate: " + String(rawstate));
  #endif
  
  //extract state
  int state = rawstate.toInt();
  
  //check state
  if (state != 1) state = 0;

  #ifdef debugmode
    Serial.println("state: " + String(state));
  #endif
  
  //set pin
  digitalWrite(output_pin, state);

    
  //go to lightsleep
  lightsleep(requesttimeout);
  
}
