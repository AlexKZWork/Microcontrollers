#include <Wire.h>

void setup() {
  // Инициализируем Wire (I2C) с произвольными пинами SDA и SCL
  Wire.setSDA(16);
  Wire.setSCL(17);
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Поиск I2C устройств...");

  byte address;
  int devicesFound = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Устройство найдено по адресу 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);      
      devicesFound++;
    }
  }

  if (devicesFound == 0) {
    Serial.println("I2C устройства не найдены.");
  } else {
    Serial.print("Всего устройств: ");
    Serial.println(devicesFound);
  }
}

void loop() {  
}
