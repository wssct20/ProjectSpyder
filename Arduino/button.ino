
const int buttonPin = 5;
const int LED_BUILTIN = 2;

void buttonsetup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

void buttonloop() {
/*
  if (digitalRead(buttonPin) == HIGH)
  {
    Serial.println("button LOW");
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    Serial.println("button HIGH");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(50);
*/
  delay(10000);
}
