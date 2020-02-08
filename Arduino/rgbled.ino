
#define pincount 3                    //number of pins you use
const int pins[] = {19, 18, 5};       //Enter the pin of your led here

#define rgbled_frequency 5000                //pwm frequency
#define pwmchannelcount 3                    //number of pwm channels you use
const int rgbled_pwmchannel[] = {0, 1, 2};   //pwm channels
#define rgbled_resolution 8                  //8-bit resolution



void rgbledsetup() {

  //setup channels and link pins
  for (int i = 0; i < pwmchannelcount; i++)
  {
    ledcSetup(rgbled_pwmchannel[i], rgbled_frequency, rgbled_resolution);
    ledcAttachPin(pins[i], rgbled_pwmchannel[i]);
  }

  putstate("255:255:255");    //only a test state. red:green:blue
  
}

void rgbledloop() {

  Serial.println("rgbled() look for state");

  String rawstate = getstate();       //get state from system
  Serial.print("rawstate: ");
  Serial.println(rawstate);

  //catch wrong format
  if (rawstate.indexOf(":") == -1) rawstate = "0:0:0";
  
  //search for seperators
  int seperator1 = rawstate.indexOf(":");
  Serial.print("seperator1: ");
  Serial.println(seperator1);
  
  int seperator2 = rawstate.indexOf(":", seperator1 + 1);
  Serial.print("seperator2: ");
  Serial.println(seperator2);
  
  //extract states
  int state[] = {
    rawstate.substring(0, seperator1).toInt(),
    rawstate.substring(seperator1 + 1, seperator2).toInt(),
    rawstate.substring(seperator2 + 1).toInt(),
  };

  //check state
  for (int i = 0; i < pincount; i++)
  {
    if (state[i] < 0 | state[i] > 255) state[i] = 0;
  }
  
  //set pins
  for (int i = 0; i < pincount; i++)
  {
    ledcWrite(rgbled_pwmchannel[i], state[i]);
  }

  Serial.print("redstate: ");
  Serial.println(state[0]);
  Serial.print("greenstate: ");
  Serial.println(state[1]);
  Serial.print("bluestate: ");
  Serial.println(state[2]);
  
  //go to lightsleep
  lightsleep(requesttimeout);
  
}
