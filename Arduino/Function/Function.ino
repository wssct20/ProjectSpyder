
const int buttonPin = 5;

void setup() {

  wifi();
  php();

  pinMode(buttonPin, INPUT);

}

void loop() {

  if (digitalRead(buttonPin) == HIGH)
  {
    Serial.println("button LOW");
  }
  else {
    Serial.println("button HIGH");
  }
  delay(1000);
}
