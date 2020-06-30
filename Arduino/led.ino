
#define led_pin 5               //Enter the pin of your led here

#define led_frequency 5000      //pwm frequency
#define led_pwmchannel 0        //pwm channel
#define led_resolution 8        //8-bit resolution



void ledsetup() {

  //setup channels and link pins
  ledcSetup(led_pwmchannel, led_frequency, led_resolution);
  ledcAttachPin(led_pin, led_pwmchannel);

  //set client specific jsonstructure
  jsonstructure = "{\
\"data\":{\
\"brightness\":0\
},\
\"usermodifiabledata\":[\"brightness\"],\
\"friendly\":{\
\"datavar\":{\
\"brightness\":\"Brightness\"\
},\
\"type\":\"LED\"\
},\
\"preferredupdatetime\":5\
}";
  
}

void ledloop() {

  #ifdef debugmode
    Serial.println("ledloop()");
  #endif

  //get data from system
  DynamicJsonDocument data(JSONCAPACITY);
  deserializeJson(data, getdata());

  uint8_t brightness = data["data"]["brightness"].as<uint8_t>();

  #ifdef debugmode
    Serial.println("brightness: " + String(brightness));
  #endif
  
  //set pin
  ledcWrite(led_pwmchannel, brightness);

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
