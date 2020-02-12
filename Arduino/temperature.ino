#include "DHTesp.h"

#define datapin 5

/*
 * Connection:
 * +    to 3.3V-5V DC
 * -    to GND (common ground)
 * out  to a digital Pin
 */

//initialise the sensor
DHTesp dht;

//task handle for the light value read task
TaskHandle_t tempTaskHandle = NULL;

void temperaturesetup() {

  //initialize temperature sensor
  dht.setup(datapin, DHTesp::DHT22);
  
}

void temperatureloop() {

  TempAndHumidity lastValues = dht.getTempAndHumidity();

  #ifdef debugmode
    Serial.println("Temperature: " + String(lastValues.temperature, 1));
    Serial.println("Humidity: " + String(lastValues.humidity, 1));
  #endif

  String state = String(lastValues.temperature);
  state.concat(":");
  state.concat(lastValues.humidity);

  #ifdef debugmode
    Serial.println("state: " + String(state));
  #endif
  
  //send the values to the server
  putstate(state);
  
  lightsleep(requesttimeout);
  
}
