
#define pincount 3                    //number of pins you use
const int pins[] = {19, 18, 5};       //Enter the pin of your led here

#define rgbled_frequency 5000                //pwm frequency
#define pwmchannelcount 3                    //number of pwm channels you use
const int rgbled_pwmchannel[] = {0, 1, 2};   //pwm channels
#define rgbled_resolution 8                  //8-bit resolution



void rgbledsetup() {

  //setup channels and link pins
  for (int i = 0; i < pwmchannelcount; i++) {
    ledcSetup(rgbled_pwmchannel[i], rgbled_frequency, rgbled_resolution);
    ledcAttachPin(pins[i], rgbled_pwmchannel[i]);
  }

  //set client specific jsonstructure
  jsonstructure = "{\
\"data\":{\
\"red\":0,\
\"green\":0,\
\"blue\":0\
},\
\"usermodifiabledata\":[\"red\",\"green\",\"blue\"],\
\"friendly\":{\
\"datavar\":{\
\"red\":\"Red\",\
\"green\":\"Green\",\
\"blue\":\"Blue\"\
},\
\"type\":\"RGB-LED\"\
},\
\"preferredupdatetime\":5\
}";
  
}

void rgbledloop() {

  #ifdef debugmode
    Serial.println("rgbledloop()");
  #endif

  //get data from system
  DynamicJsonDocument data(JSONCAPACITY);
  deserializeJson(data, getdata());

  uint8_t pindata[] = {
    data["data"]["red"].as<uint8_t>(),
    data["data"]["green"].as<uint8_t>(),
    data["data"]["blue"].as<uint8_t>(),
  };
  
  //set pins
  for (int i = 0; i < pincount; i++) {
    ledcWrite(rgbled_pwmchannel[i], pindata[i]);
  }

  #ifdef debugmode
    Serial.println("red: " + String(pindata[0]));
    Serial.println("green: " + String(pindata[1]));
    Serial.println("blue: " + String(pindata[2]));
  #endif
  
  //go to lightsleep
  lightsleep(requesttimeout);
  
}
