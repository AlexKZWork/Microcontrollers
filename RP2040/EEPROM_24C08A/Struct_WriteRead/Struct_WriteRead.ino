#include <Wire.h>

#define EEPROM_ADDR 0x50  // Адрес EEPROM
#define STRUCT_START_ADDR 0  // Начальный адрес для хранения структуры

// Тестовая структура для записи-чтения
struct UserProfile {
  char name[10];
  uint8_t age;
  uint32_t score;
};

UserProfile profile = {"Alex", 41, 1000};

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while (!Serial);

  Serial.println("Запись данных в EEPROM...");
  writeStruct(STRUCT_START_ADDR, profile);

  Serial.println("Чтение данных из EEPROM...");
  UserProfile readProfile;
  readStruct(STRUCT_START_ADDR, readProfile);

  Serial.print("Имя: ");
  Serial.println(readProfile.name);
  Serial.print("Возраст: ");
  Serial.println(readProfile.age);
  Serial.print("Очки: ");
  Serial.println(readProfile.score);
}

void loop() {}

// Функция записи структуры в EEPROM
void writeStruct(int address, UserProfile &data) { // &data - ссылка на оригинальную структуру типа UserProfile
  byte *ptr = (byte *)&data; // Побайтовое преобразование указателя
  int structSize = sizeof(UserProfile);

  for (int i = 0; i < structSize; i++) {
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write(address + i);
    Wire.write(*(ptr + i));
    Wire.endTransmission();
    delay(5);  // Задержка для завершения записи в EEPROM
  }
}

// Функция чтения структуры из EEPROM
void readStruct(int address, UserProfile &data) { // &data - ссылка на оригинальную структуру типа UserProfile
  byte *ptr = (byte *)&data; // Побайтовое преобразование указателя
  int structSize = sizeof(UserProfile);

  for (int i = 0; i < structSize; i++) {
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write(address + i);
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_ADDR, 1);
    if (Wire.available()) {
      *(ptr + i) = Wire.read();
    }
  }
}
