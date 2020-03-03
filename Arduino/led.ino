
#define led_pin 5               //Enter the pin of your led here

#define led_frequency 5000      //pwm frequency
#define led_pwmchannel 0        //pwm channel
#define led_resolution 8        //8-bit resolution



void ledsetup() {

  //setup channels and link pins
  ledcSetup(led_pwmchannel, led_frequency, led_resolution);
  ledcAttachPin(led_pin, led_pwmchannel);

  jsonstructure = "{\"data\":{\"data\":{\"brightness\":0},\"usermodifiabledata\":[\"brightness\"],\"friendly\":{\"datavar\":{\"brightness\":\"Brightness\"},\"led\":\"LED\"},\"preferredupdatetime\":2}}";
  
}

void ledloop() {

  #ifdef debugmode
    Serial.println("led() look for data");
  #endif

  //get data from system
  DynamicJsonDocument data(JSONCAPACITY);
  deserializeJson(data, getdata());

  int brightness = data["data"]["brightness"].as<int>();

  //check data
  if ((brightness < 0) || (brightness > 255)) brightness = 0;

  #ifdef debugmode
    Serial.println("brightness: " + String(brightness));
  #endif
  
  //set pin
  ledcWrite(led_pwmchannel, brightness);

  //go to lightsleep
  lightsleep(requesttimeout);
  
}
