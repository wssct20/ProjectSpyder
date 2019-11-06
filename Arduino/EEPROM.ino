#include "EEPROM.h"


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
