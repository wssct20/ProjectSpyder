
#define led_pin 5               //Enter the pin of your led here

#define led_frequency 5000      //pwm frequency
#define led_pwmchannel 0        //pwm channel
#define led_resolution 8        //8-bit resolution



void ledsetup() {

  //setup channels and link pins
  ledcSetup(led_pwmchannel, led_frequency, led_resolution);
  ledcAttachPin(led_pin, led_pwmchannel);

  putstate("150");    //only a test state.
  
}

void ledloop() {

  #ifdef debugmode
    Serial.println("led() look for state");
  #endif

  //get state from system
  String rawstate = getstate();
  #ifdef debugmode
    Serial.println("rawstate: " + String(rawstate));
  #endif
  
  //extract state
  int state = rawstate.toInt();
  
  //check state
  if ((state < 0) | (state > 255)) state = 0;

  #ifdef debugmode
    Serial.println("state: " + String(state));
  #endif
  
  //set pin
  ledcWrite(led_pwmchannel, state);

    
  //go to lightsleep
  lightsleep(requesttimeout);
  
}
