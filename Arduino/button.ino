#define buttonPin 4
#define LED_BUILTIN 2
//#define touchthreshold 40

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  requesttimeout = 1;

}

void buttonloop() {
  
  bool buttonstate = lightsleepgpio(requesttimeout, buttonPin, 0);
  digitalWrite(LED_BUILTIN, buttonstate ? HIGH : LOW);
  Serial.print("Button state: ");
  Serial.println(buttonstate);
  
  //delay(5000);
  putstate(String(!buttonstate));
  
}
