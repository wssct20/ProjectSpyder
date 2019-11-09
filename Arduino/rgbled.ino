
#define pincount 3                    //number of pins you use
const int pins[] = {19, 18, 5};       //Enter the pin of your led here

const int frequenz = 5000;            //pwm frequenz
#define pwmchannelcount 3             //number of pwm channels you use
const int pwmchannel[] = {0, 1, 2};   //pwm channels
const int resolution = 8;             //8-bit resolution



void rgbledsetup() {

  Serial.println("rgbledsetup");

  //setup channels and link pins
  for (int i = 0; i < pwmchannelcount; i++)
  {
    ledcSetup(pwmchannel[i], frequenz, resolution);
    ledcAttachPin(pins[i], pwmchannel[i]);
  }

  putstate("0-150-0");    //only a test state. red-green-blue
  
}

void rgbledloop() {

  Serial.println("rgbled() look for state");

  String rawstate = getstate();       //get state from system
  Serial.print("rawstate: ");
  Serial.println(rawstate);

  //catch wrong format
  if (rawstate.indexOf("-") == -1) rawstate = "0-0-0";
  
  //search for seperators
  int seperator1 = rawstate.indexOf("-");
  Serial.print("seperator1: ");
  Serial.println(seperator1);
  
  int seperator2 = rawstate.indexOf("-", seperator1 + 1);
  Serial.print("seperator2: ");
  Serial.println(seperator2);
  
  //extract states
  int state[] = {
    rawstate.substring(0, seperator1).toInt(),
    rawstate.substring(seperator1 + 1, seperator2).toInt(),
    rawstate.substring(seperator2 + 1).toInt(),
  };

  //set pins
  for (int i = 0; i < pincount; i++)
  {
    ledcWrite(pins[i], state[i]);
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
