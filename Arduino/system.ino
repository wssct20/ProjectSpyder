#include "EEPROM.h"

//////////////EEPROM//////////////
void writeEEPROM(int address, int length, String data)
{
  Serial.println("writeEEPROM start");
  EEPROM.begin(address + length);

  Serial.print("address: ");
  Serial.println(address);
  Serial.print("length: ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.println(data);

  char dataarray[length + 1];
  data.toCharArray(dataarray, length + 1);
  for (int i = 0; i < length; i++)
  {
    if (EEPROM.read(address + i) != dataarray[i]) EEPROM.write(address + i, dataarray[i]);
  }
  EEPROM.commit();
}


String readEEPROM(int address, int length)
{
  Serial.println("readEEPROM start");

  Serial.print("address: ");
  Serial.println(address);
  Serial.print("length: ");
  Serial.println(length);
  Serial.print("read data: ");

  char dataarray[length];
  for (int i = 0; i < length; i++)
  {
    dataarray[i] = EEPROM.read(address + i);
    Serial.print(dataarray[i]);
  }
  Serial.println();
  return String(dataarray);
}


//////////////sleep//////////////
void lightsleep(int seconds)
{
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  Serial.print("Starting lightsleep for ");
  Serial.print(seconds);
  Serial.println(" seconds.");
  #if debugmode == true
  delay(1000);
  #endif
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();
  Serial.println("lightsleep ended");
  esp_wifi_start();
  wifisetup();
}


void hibernate(int seconds)
{
  Serial.print("Go to Hibernation for ");
  Serial.print(seconds);
  Serial.println(" seconds.");
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_wifi_disconnect();
  esp_wifi_stop();
  delay(1000);
  #if debugmode == true
  delay(5000);
  #endif
  esp_deep_sleep_start();
  //after hibernation the ESP32 will restart
  //this function will not return
}
