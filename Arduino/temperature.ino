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

  jsonstructure = "{\
\"data\":{\
\"temperature\":0,\
\"humidity\":0\
},\
\"friendly\":{\
\"datavar\":{\
\"temperature\":\"Temperature\",\
\"humidity\":\"Humidity\"\
},\
\"datavalue\":{\
\"temperature\":\"0°C\",\
\"humidity\":\"0%\"\
},\
\"type\":\"Temperature Sensor\"\
},\
\"preferredupdatetime\":30\
}";
  
}

void temperatureloop() {

  #ifdef debugmode
    Serial.println("temperatureloop()");
  #endif

  String temperaturedata;

  TempAndHumidity lastValues = dht.getTempAndHumidity();

  #ifdef debugmode
    Serial.println("Temperature: " + String(lastValues.temperature, 1));
    Serial.println("Humidity: " + String(lastValues.humidity, 1));
  #endif

  DynamicJsonDocument datadoc(JSONCAPACITY);
  
  JsonObject data = datadoc.createNestedObject("data");
  data["temperature"] = lastValues.temperature;
  data["humidity"] = lastValues.humidity;

  JsonObject friendly = datadoc.createNestedObject("friendly");
  JsonObject datavalue = friendly.createNestedObject("datavalue");
  String friendlytemperature = String(lastValues.temperature);
  friendlytemperature.concat("°C");
  datavalue["temperature"] = friendlytemperature;
  String friendlyhumidity = String(lastValues.humidity);
  friendlyhumidity.concat("%");
  datavalue["humidity"] = friendlyhumidity;
  
  serializeJson(datadoc, temperaturedata);
  
  //send the values to the server
  updatedata(temperaturedata);
  
  lightsleep(requesttimeout);
  
}
