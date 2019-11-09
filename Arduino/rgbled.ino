#define redpin 1
#define greenpin 2
#define bluepin 3



void rgbledstripsetup() {

  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
}

void rgbledstriploop() {

/*  wert = getstate();
  
  digitalWrite(redpin, wert);
  digitalWrite(greenpin, wert);
  digitalWrite(bluepin, wert);*/

  Serial.println("getstate() start: ");
  Serial.println(getstate());
  delay(10000);
  
}
