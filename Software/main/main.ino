
#include <Wire.h>
#include "ALS31300.h"

int hall_mode = 0;
ALS31300 DUT(96);

void setup()
{
  Wire.begin();
  Wire.setClock(1000000);
  Serial.begin(115200);

  DUT.unlock();

  auto EEPROM1 = DUT.read(RegMap::BW_Select);
  DUT.setValue(RegMap::BW_Select, EEPROM1, 0);
  DUT.write(RegMap::BW_Select, EEPROM1);
  Serial.print("BW_Select: ");
  Serial.println(EEPROM1);

  auto EEPROM2 = DUT.read(RegMap::BW_Select);
  Serial.println(DUT.getValue(RegMap::BW_Select, EEPROM2));
}

byte val = 0;

void loop()
{
  auto data = DUT.readFull();
  Serial.println(data.z);
  delay(500);
}
