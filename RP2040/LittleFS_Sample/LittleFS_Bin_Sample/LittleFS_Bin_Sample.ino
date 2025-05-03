#include <LittleFS.h>

constexpr char FILE_PATH[] = "/settings/config.bin";

// Структура для примера
struct Config {
    int id;
    float value;
    char name[10];
};

void setup() {
    Serial.begin(115200);
    while (!Serial) ; // Ожидание готовности Serial
    Serial.println("Инициализация файловой системы...");
    if (!LittleFS.begin()) {
        Serial.println("Ошибка инициализации файловой системы!");
        return;
    }
    Serial.println("Инициализация прошла успешно.");

    // Заполняем структуру
    Config cfg = {1, 3.14, "RP2040"};

    // Запись структуры в файл    
    File file = LittleFS.open(FILE_PATH, "w");
    Serial.println("Открытие файла для записи...");
    if (!file){
      Serial.println("Ошибка открытия файла!");
      return;
    }
    Serial.println("Запись структуры в файл...");
    file.write((uint8_t*)&cfg, sizeof(cfg));
    file.close();
    Serial.println("Структура записана успешно.");

    // Чтение структуры из файла
    Serial.println("Открытие файла для чтения...");    
    file = LittleFS.open(FILE_PATH, "r");
    if (!file){
      Serial.println("Ошибка открытия файла!");
      return;
    }
    Serial.println("Чтение из файла...");
    Config readCfg;
    file.read((uint8_t*)&readCfg, sizeof(readCfg));
    file.close();

    // Вывод в Serial
    Serial.print("ID: "); Serial.println(readCfg.id);
    Serial.print("Value: "); Serial.println(readCfg.value);
    Serial.print("Name: "); Serial.println(readCfg.name);
}

void loop() {  
}
