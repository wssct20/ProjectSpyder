
#define buttonPin 5
#define LED_BUILTIN 2

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

void buttonloop() {

  bool buttonstate;
  if (digitalRead(buttonPin) == HIGH)
  {
    Serial.println("button LOW");
    digitalWrite(LED_BUILTIN, LOW);
    buttonstate = false;
  }
  else {
    Serial.println("button HIGH");
    digitalWrite(LED_BUILTIN, HIGH);
    buttonstate = true;
  }
  //delay(50);
  putstate(String(buttonstate));
  lightsleep(requesttimeout);
}
