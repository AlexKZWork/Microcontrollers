// Функция которая показывает 8-и битное число полностью (с ведущими нолями)
void printByteBin(uint8_t val) {
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(val, i));
  }
}

void setup() {
  Serial.begin(9600);
  uint8_t x = 0b00011001;
  printByteBin(x);
  Serial.println(" Оригинал");
  printByteBin((x << 1));
  Serial.println(" Сдвиг оригинала влево на один разряд");
  printByteBin((x >> 1));
  Serial.println(" Сдвиг оригинала вправо на один разряд\n");

  uint8_t a = 5;
  Serial.print("Сдвиг влево на один разряд числа ");
  Serial.print(a);
  Serial.print(" результат ");
  Serial.println((a << 1));

  Serial.print("Сдвиг влево на два разряда числа ");
  Serial.print(a);
  Serial.print(" результат ");
  Serial.println((a << 2));

  Serial.print("Сдвиг вправо на один разряд числа ");
  Serial.print(a);
  Serial.print(" результат ");
  Serial.println((a >> 1));

  a = 0b10011010;
  uint8_t b = 0b01101100;
  Serial.println("\nЛогическое И (AND)");
  printByteBin(a);
  Serial.print(" & ");
  printByteBin(b);
  Serial.print(" = ");
  printByteBin((a & b));
  Serial.println();

  Serial.println("\nЛогическое ИЛИ (OR)");
  printByteBin(a);
  Serial.print(" | ");
  printByteBin(b);
  Serial.print(" = ");
  printByteBin((a | b));
  Serial.println();

  Serial.println("\nЛогическое исключающее ИЛИ (XOR)");
  printByteBin(a);
  Serial.print(" ^ ");
  printByteBin(b);
  Serial.print(" = ");
  printByteBin((a ^ b));
  Serial.println();

  Serial.println("\nЛогическое НЕ (NOT)");
  Serial.print("~");
  printByteBin(a);
  Serial.print(" = ");
  printByteBin(~(a));  
  Serial.println();

  // Вот так можно проверять включен ли бит (для примера шестой)
  a = 0b01111100;
  Serial.println("\nПроверка включен ли бит 6 в значении ");
  printByteBin(a);
  if (a & (1 << 6)) {
    Serial.println("\nВключен");
  }
  else {
    Serial.println("\nВыключен");
  }

  // Вот так можно проверять включены ли несколько бит (называется сравнение по маске, для примера будем сравнивать 3 последних бита)
  a = 0b01011100;
  uint8_t mask = 0b00000111;
  Serial.print("\nПроверка включены ли биты по маске ");
  printByteBin(mask);
  Serial.print(" в значении ");
  printByteBin(a);  
  if ((a & mask) == mask) {
    Serial.println("\nВключены");
  }
  else {
    Serial.println("\nВыключены или выключены некоторые");
  }

  // Установка бита в 0 (для примера будет третий, напоминаю счет начинается справа налево самый правый 0, а самый левый 7)
  a = 0b11111111;
  Serial.println("\nУстановка бита 3 в 0");
  printByteBin(a);
  Serial.println(" оригинал");
  a &= ~(1 << 3);
  printByteBin(a);
  Serial.println(" результат");
}

void loop() {
}
