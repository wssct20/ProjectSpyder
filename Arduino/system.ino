#include "EEPROM.h"
#include "esp_sleep.h"
//#include "rtc_io.h"

//////////////EEPROM//////////////
void writeEEPROM(int address, int length, String data) {
  #ifdef debugmode
    Serial.println("writeEEPROM() start");
  #endif
  EEPROM.begin(address + length);

  #ifdef debugmode
    Serial.println("address: " + String(address));
    Serial.println("length: " + String(length));
    Serial.println("data: " + String(data));
  #endif

  char dataarray[length + 1];
  data.toCharArray(dataarray, length + 1);
  for (int i = 0; i < length; i++) {
    if (EEPROM.read(address + i) != dataarray[i]) EEPROM.write(address + i, dataarray[i]);
  }
  EEPROM.commit();
}


String readEEPROM(int address, int length) {
  #ifdef debugmode
    Serial.println("readEEPROM() start");
  #endif
  EEPROM.begin(address + length);

  #ifdef debugmode
    Serial.println("address: " + String(address));
    Serial.println("length: " + String(length));
    Serial.print("read data: ");
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
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  #ifdef debugmode
    Serial.println("Starting lightsleep for " + String(seconds) + String(" seconds."));
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
    Serial.println("----continue-----");
  #endif
  esp_wifi_start();
  wifisetup();
}

bool lightsleepgpio(int seconds, int pin, bool triggerlevel) {
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  gpio_wakeup_enable((gpio_num_t)pin, triggerlevel?GPIO_INTR_HIGH_LEVEL:GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  #ifdef debugmode
    Serial.println("Starting lightsleep for " + String(seconds) + String(" seconds."));
    Serial.println("Added interrupt for Pin " + String(pin) + String(" for state ") + String(triggerlevel) + String("."));
    Serial.println("------sleep------");
  #endif
  #ifdef debugmode
    delay(1000);
  #endif
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();
  bool pinstate = digitalRead(pin) == HIGH ? true : false;
  #ifdef debugmode
    Serial.println("lightsleep ended");
    Serial.println("----continue-----");
  #endif
  esp_wifi_start();
  wifisetup();
  return pinstate;
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
    Serial.println("----continue-----");
  #endif
  esp_wifi_start();
  wifisetup();
}
*/


void hibernate(int seconds) {
  #ifdef debugmode
    Serial.println("Go to Hibernation for " + String(seconds) + String(" seconds."));
  #endif
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
  esp_deep_sleep_start();
  //after hibernation the ESP32 will restart
  //this function will not return
}


//////////////converter//////////////

//hextodec() converts hex numbers to dec numbers (max. 8 bytes)
uint32_t hextodec(String hex) {
  String hexnumbers = "0123456789ABCDEF";
  uint32_t dec = 0;
  
  for(int i = (hex.length() - 1); i >= 0; i--) {
    String hex0 = hex.substring(i, i + 1);
    dec += (uint32_t)hexnumbers.indexOf(hex0) << (hex.length() - 1 - i) * 4;
  }
  return dec;
}

//dectohex() converts dec numbers to hex numbers
String dectohex(uint32_t dec) {
  String hexnumbers = "0123456789ABCDEF";
  String hex = "";

  int i = 0;
  uint8_t num = 0;
  do {
    num = (dec & ((uint32_t)15 << (4 * i))) >> (4 * i);
    String singlehex = hexnumbers.substring(num, num + 1);
    singlehex.concat(hex);
    hex = singlehex;
    i++;
  }
  while(num != 0 && i < 8);
  if(i < 8 && num == 0) {
    hex = hex.substring(1);
  }
  return hex;
}


//////////////color management//////////////

//hextorgb() converts hex colordata to rgb colordata
color_t hextorgb(uint32_t hex) {
  color_t color;
  color.red = (hex & 0xFF0000) >> 16;
  color.green = (hex & 0xFF00) >> 8;
  color.blue = hex & 0xFF;
  return color;
}
