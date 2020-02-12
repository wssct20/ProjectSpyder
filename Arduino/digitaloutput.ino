
#define output_pin 5

void digitaloutputsetup() {

  digitalWrite(output_pin, LOW);
  
  putstate("1");    //only a test state
  
}

void digitaloutputloop() {

  Serial.println("digitaloutput() look for state");

  //get state from system
  String rawstate = getstate();
  Serial.println("rawstate: " + String(rawstate));
  
  //extract state
  int state = rawstate.toInt();
  
  //check state
  if (state != 1) state = 0;

  Serial.println("state: " + String(state));
  
  //set pin
  digitalWrite(output_pin, state);

    
  //go to lightsleep
  lightsleep(requesttimeout);
  
}
