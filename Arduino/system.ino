#include "EEPROM.h"
#include "esp_sleep.h"
//#include "rtc_io.h"

//////////////EEPROM//////////////
void writeEEPROM(int address, int length, String data)
{
  Serial.println("writeEEPROM() start");
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
  Serial.println("readEEPROM() start");
  EEPROM.begin(address + length);

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
  if (seconds < 10) {
    Serial.println("Lightsleep not needed for less than 10s, staying awake.");
    delay(seconds * 1000);
    Serial.println("Delay ended.");
    return;
  }
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  Serial.print("Starting lightsleep for ");
  Serial.print(seconds);
  Serial.println(" seconds.");
  Serial.println("------sleep------");
  #ifdef debugmode
  delay(1000);
  #endif
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();
  Serial.println("lightsleep ended");
  Serial.println("----continue-----");
  esp_wifi_start();
  wifisetup();
}

bool lightsleepgpio(int seconds, int pin, bool triggerlevel)
{
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  gpio_wakeup_enable((gpio_num_t)pin, triggerlevel?GPIO_INTR_HIGH_LEVEL:GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  Serial.print("Starting lightsleep for ");
  Serial.print(seconds);
  Serial.println(" seconds.");
  Serial.print("Added interrupt for Pin ");
  Serial.print(pin);
  Serial.print(" for state ");
  Serial.print(triggerlevel);
  Serial.println(".");
  Serial.println("------sleep------");
  #ifdef debugmode
  delay(1000);
  #endif
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();
  bool pinstate = digitalRead(pin) == HIGH ? true : false;
  Serial.println("lightsleep ended");
  Serial.println("----continue-----");
  esp_wifi_start();
  wifisetup();
  return pinstate;
}

//TODO: implement lightsleep touch wakeup
/*
void touchcallback(){
  //Serial.println("touchcallback");
}

void lightsleeptouch(int seconds, int touchpin, int threshold)
{
  esp_sleep_enable_timer_wakeup(seconds * 1000000);
  touchAttachInterrupt(touchpin, touchcallback, threshold);
  esp_sleep_enable_touchpad_wakeup();
  Serial.print("Starting lightsleep for ");
  Serial.print(seconds);
  Serial.println(" seconds.");
  Serial.print("Added touch interrupt for Pin ");
  Serial.print(touchpin);
  Serial.println(".");
  Serial.println("------sleep------");
  #ifdef debugmode
  delay(1000);
  #endif
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_light_sleep_start();
  Serial.println("lightsleep ended");
  Serial.println("----continue-----");
  esp_wifi_start();
  wifisetup();
}
*/


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
  #ifdef debugmode
  delay(5000);
  #endif
  esp_deep_sleep_start();
  //after hibernation the ESP32 will restart
  //this function will not return
}


//////////////converter//////////////

//hextodec() converts hex numbers to dec numbers (max. 8 bytes)
uint32_t hextodec(String hex)
{
  String hexnumbers = "0123456789ABCDEF";
  uint32_t dec = 0;
  
  for(int i = (hex.length() - 1); i >= 0; i--){
    String hex0 = hex.substring(i, i + 1);
    dec += (uint32_t)hexnumbers.indexOf(hex0) << (hex.length() - 1 - i) * 4;
  }
  return dec;
}

//dectohex() converts dec numbers to hex numbers
String dectohex(uint32_t dec)
{
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
  if(i < 8 && num == 0){
    hex = hex.substring(1);
  }
  return hex;
}
