
#define buttonPin 5
#define LED_BUILTIN 2

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

void buttonloop() {

  bool buttonstate = digitalRead(buttonPin) == HIGH ? true : false;
  digitalWrite(LED_BUILTIN, buttonstate ? HIGH : LOW);
  Serial.print("Button state: ");
  Serial.println(buttonstate);
  
  //delay(5000);
  putstate(String(buttonstate));
  lightsleep(requesttimeout);
}
