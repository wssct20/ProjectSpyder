
#define buttonPin 4
#define LED_BUILTIN 2
//#define touchthreshold 40

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  requesttimeout = 1;

}

void buttonloop() {
  
//  bool buttonstate = lightsleepgpio(requesttimeout, buttonPin, 0);
  bool buttonstate = false;
  lightsleep(10);
  digitalWrite(LED_BUILTIN, buttonstate ? HIGH : LOW);
  #ifdef debugmode
    Serial.println("Button state: " + String(buttonstate));
  #endif
  
  //delay(5000);
  putstate(String(!buttonstate));
  
}
