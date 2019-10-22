#include "ESP32_code_filepath.h"

const int buttonPin = 5;
const int LED_BUILTIN = 2;

void setup() {
  
  Serial.begin(115200);

  wifi();
  php();

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
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
  delay(1000);
*/

  php();
  delay(5000);
}
