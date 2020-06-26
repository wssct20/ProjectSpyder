#include "EEPROM.h"
#include "esp_sleep.h"
//#include "rtc_io.h"

//////////////EEPROM//////////////
//writes data to EEPROM (memory)
void writeEEPROM(int address, int length, String data) {
  #ifdef debugmode
    Serial.println("writeEEPROM() start");
  #endif
  EEPROM.begin(address + length);

  #ifdef debugmode
    Serial.println("address:" + String("\t") + String(address));
    Serial.println("length:" + String("\t") + String(length));
    Serial.println("data:" + String("\t") + String(data));
  #endif

  char dataarray[length + 1];
  data.toCharArray(dataarray, length + 1);
  for (int i = 0; i < length; i++) {
    if (EEPROM.read(address + i) != dataarray[i]) EEPROM.write(address + i, dataarray[i]);
  }
  EEPROM.commit();
}

//reads data from EEPROM (memory)
String readEEPROM(int address, int length) {
  #ifdef debugmode
    Serial.println("readEEPROM() start");
  #endif
  EEPROM.begin(address + length);

  #ifdef debugmode
    Serial.println("address:" + String("\t") + String(address));
    Serial.println("length:" + String("\t") + String(length));
    Serial.print("read data:" + String("\t"));
  #endif

  char dataarray[length];
  for (int i = 0; i < length; i++) {
    dataarray[i] = EEPROM.read(address + i);
    #ifdef debugmode
      Serial.print(dataarray[i]);
    #endif
  }
  #ifdef debugmode
    Serial.println();
  #endif
  return String(dataarray);
}


//////////////sleep//////////////
void lightsleep(int seconds) {
  if (seconds < 10) {
    #ifdef debugmode
      Serial.println("Lightsleep not needed for less than 10s, staying awake.");
    #endif
    delay(seconds * 1000);
    #ifdef debugmode
      Serial.println("Delay ended.");
    #endif
    return;
  }
  esp_sleep_enable_timer_wakeup(seconds * 1000000); //enable timer wakeup
  #ifdef debugmode
    Serial.println("Starting lightsleep for " + String(seconds) + String(" seconds."));
    Serial.println("------sleep------");
    delay(1000);
  #endif
  //switch off wifi
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();  //starts the lightsleep
  #ifdef debugmode
    Serial.println("lightsleep ended");
    Serial.println("-----continue-----");
  #endif
  //starts wifi
  esp_wifi_start();
  wifisetup();
}

void lightsleepgpio(int seconds, int pin, bool triggerlevel) {
  esp_sleep_enable_timer_wakeup(seconds * 1000000); //enable time wakeup
  gpio_wakeup_enable((gpio_num_t)pin, triggerlevel?GPIO_INTR_HIGH_LEVEL:GPIO_INTR_LOW_LEVEL); //initialise gpio wakeup
  esp_sleep_enable_gpio_wakeup(); //enable gpio wakeup
  #ifdef debugmode
    Serial.println("Starting lightsleep for " + String(seconds) + String(" seconds."));
    Serial.println("Added interrupt for Pin " + String(pin) + String(" for state ") + String(triggerlevel) + String("."));
    Serial.println("------sleep------");
  #endif
  #ifdef debugmode
    delay(1000);
  #endif
  //switch off wifi
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();  //starts the lightsleep
  #ifdef debugmode
    Serial.println("lightsleep ended");
    Serial.println("-----continue-----");
  #endif
  //starts wifi
  esp_wifi_start();
  wifisetup();
  return;
}

//TODO: implement lightsleep touch wakeup
/*
void touchcallback() {
  //Serial.println("touchcallback");
}

void lightsleeptouch(int seconds, int touchpin, int threshold) {
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  touchAttachInterrupt(touchpin, touchcallback, threshold);
  esp_sleep_enable_touchpad_wakeup();
  #ifdef debugmode
    Serial.println("Starting lightsleep for " + String(seconds) + String(" seconds."));
    Serial.println("Added touch interrupt for Pin " + String(touchpin) + String("."));
    Serial.println("------sleep------");
  #endif
  #ifdef debugmode
    delay(1000);
  #endif
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();
  #ifdef debugmode
    Serial.println("lightsleep ended");
    Serial.println("-----continue-----");
  #endif
  esp_wifi_start();
  wifisetup();
}
*/


void hibernate(int seconds) {
  #ifdef debugmode
    Serial.println("Go to Hibernation for " + String(seconds) + String(" seconds."));
  #endif
  //switches off functions which are not needed during hibernation
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_wifi_disconnect();
  esp_wifi_stop();
  delay(1000);
  #ifdef debugmode
    delay(5000);
  #endif
  esp_deep_sleep_start(); //starts the hibernation
  //after hibernation the ESP32 will restart
  //this function will not return
}
