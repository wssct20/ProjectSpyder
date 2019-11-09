#define redpin 1        //Enter the pin of your red led here
#define greenpin 2      //Enter the pin of your green led here
#define bluepin 3       //Enter the pin of your blue led here



void rgbledsetup() {

  Serial.println("rgbledsetup");
  
  //Set pins to output
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

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

  //array of oins
  int pins[] = {
    redpin,
    greenpin,
    bluepin,
  };

  //set pins
  for (int i = 0; i < sizeof(pins); i++)
  {
    digitalWrite(pins[i], state[i]);
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
