
const int pin = 5;      //Enter the pin of your led here

const int led_frequency = 5000;      //pwm frequency
const int led_pwmchannel = 0;       //pwm channel
const int led_resolution = 8;       //8-bit resolution



void ledsetup() {

  //setup channels and link pins
  ledcSetup(led_pwmchannel, led_frequency, led_resolution);
  ledcAttachPin(pin, led_pwmchannel);

  putstate("150");    //only a test state.
  
}

void ledloop() {

  Serial.println("led() look for state");

  String rawstate = getstate();       //get state from system
  Serial.print("rawstate: ");
  Serial.println(rawstate);
  
  //extract state
  int state = rawstate.toInt();
  
  //check state
  if (state < 0 | state > 255) state = 0;

  Serial.print("state: ");
  Serial.println(state);
  
  //set pin
  ledcWrite(led_pwmchannel, state);

    
  //go to lightsleep
  lightsleep(requesttimeout);
  
}