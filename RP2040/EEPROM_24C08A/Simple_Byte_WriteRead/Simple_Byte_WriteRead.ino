#include <Wire.h>

const byte EEPROM_ADDR_BLOCK[] = {0x50, 0x51, 0x52, 0x53}; // Адреса блоков

void setup() {
  // Установка и настройка I2C и Serial
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Тест записи и чтения одного байта в каждом блоке.\n");
  
  // Запись в EEPROM
  byte addr = 0x00; // Адрес в блоке
  byte data = 0xA5; // Тестовые данные
  int block_count = sizeof(EEPROM_ADDR_BLOCK) / sizeof(EEPROM_ADDR_BLOCK[0]); // Выясняем количество элементов в массиве адресов блоков
  Serial.print("Запись значения  '0x");
  Serial.print(data, HEX);
  Serial.print("' в каждый блок по адресу : 0x");
  Serial.println(addr, HEX);
  for (int eeprom_block = 0; eeprom_block < block_count; eeprom_block++) {
    Wire.beginTransmission(EEPROM_ADDR_BLOCK[eeprom_block]);
    Wire.write(addr);
    Wire.write(data);
    Wire.endTransmission();
    delay(5); // Ожидание записи
  }
  Serial.println();

  // Чтение из EEPROM
  byte readed_data;
  for (int eeprom_block = 0; eeprom_block < block_count; eeprom_block++) {
    Wire.beginTransmission(EEPROM_ADDR_BLOCK[eeprom_block]);
    Wire.write(addr);
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_ADDR_BLOCK[eeprom_block], 1);
    if (Wire.available()) {
      readed_data = Wire.read();
      Serial.print("Прочитанные данные из блока '0x");
      Serial.print(EEPROM_ADDR_BLOCK[eeprom_block], HEX);
      Serial.print("' : 0x");
      Serial.println(readed_data, HEX);
    } else {
      Serial.println("Ошибка чтения!");
    }
  }
}

void loop() {
}
