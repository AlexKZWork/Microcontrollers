#include <LittleFS.h>

constexpr char FILE_PATH[] = "/text.txt";

void setup() {
  Serial.begin(115200);
  while (!Serial); // Ждём Serial (если нужно)

  // Инициализация LittleFS
  Serial.println("Инициализация файловой системы.");
  if (!LittleFS.begin()) {
    Serial.println("Ошибка инициализации файловой системы!");
    return;
  }
  Serial.println("Инициализация прошла успешно.");

  // Создание и запись в файл
  Serial.println("\nЗапись в файл...");
  File file = LittleFS.open(FILE_PATH, "w"); // Открываем файл на запись, "w" = запись
  if (file) {
    file.println("Привет, RP2040!");
    file.println("Этот текст сохранён в LittleFS.");
    file.close();
    Serial.println("Файл записан.");
  } else {
    Serial.println("Ошибка создания файла!");
  }

  // Чтение из файла
  Serial.println("\nЧтение файла:");
  file = LittleFS.open(FILE_PATH, "r"); // Открываем файл на чтение, "r" = чтение
  if (file) {
    while (file.available()) {
      Serial.write(file.read()); // Выводим по символу
    }
    file.close();
    Serial.println("\nЧтение завершено.");
  } else {
    Serial.println("Ошибка открытия файла!");
  }

  // Добавление элементов в существующий файл  
  Serial.println("\nДобавление новых записей в файл...");
  file = LittleFS.open(FILE_PATH, "a"); // Открываем файл на добавление, "a" = добавить в конец
  if (file) {
    int value = 42;
    file.println("Новая строка");
    file.print("Новое целочисленное значение : ");
    file.println(value);
    file.close();
    Serial.println("Новые данные успешно добавлены.");
  }
  else {
    Serial.println("Ошибка открытия файла!");
  }  

  // Чтение из файла чтобы удостовериться в том что добавление в файл прошло успешно
  int fileSize = 0;
  Serial.println("\nЧтение файла после добавления новых данных:");
  file = LittleFS.open(FILE_PATH, "r"); // Открываем файл на чтение
  if (file) {
    while (file.available()) {
      Serial.write(file.read()); // Выводим по символу
    }
    fileSize = file.size(); // Читаем размер файла (размер вернется в байтах)
    file.close();
    Serial.println("\nЧтение завершено.");
  } else {
    Serial.println("Ошибка открытия файла!");
  }

  // Проверка, существует ли файл
  Serial.println("\nПроверка на существование файла...");
  Serial.print("Файл '");
  Serial.print(FILE_PATH);
  Serial.print("'");
  if (LittleFS.exists(FILE_PATH)) {
    Serial.println(" существует.");
  } else {      
    Serial.println(" не найден.");
  }
  Serial.print("Размер файла : ");
  Serial.print(fileSize);
  Serial.println(" байт.");
  
  // Удаление файла (если нужно)
  Serial.println("\nУдаление файла...");
  if (LittleFS.remove(FILE_PATH)) {
    Serial.println("Файл удалён.");
  } else {
    Serial.println("Ошибка удаления файла!");
  }

  // Отключение файловой системы
  LittleFS.end(); // Отключать не обязательно
}

void loop() {
}
