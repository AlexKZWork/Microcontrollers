/*
  Сгенерирует последовательность HIGH = 50 мкс. -> LOW 100 мкс. -> HIGH 70 мкс.
  Можно отрегулировать задержки и в нормальную функцию это обернуть, чтобы вызывать ее по нажатию на кнопку например.
*/



// Пины
const uint8_t outputPin = 9; // OC1A (Arduino)

// Длительности в микросекундах
const uint16_t high1_us = 50;
const uint16_t low_us   = 100;
const uint16_t high2_us = 70;

volatile uint8_t phase = 0;



void startPulseSequence() {
  cli(); // Отключаем прерывания
  phase = 0;

  // Настраиваем Timer1 в режиме CTC (WGM12), предделитель 8 (0.5 мкс на тик)
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11); // CTC, prescaler 8
  TCNT1 = 0;
  OCR1A = high1_us * 2; // 0.5 мкс на тик => *2

  TIMSK1 |= (1 << OCIE1A); // Разрешаем прерывание по совпадению

  sei(); // Включаем прерывания
}



ISR(TIMER1_COMPA_vect) {
  switch (phase) {
    case 0:
      digitalWrite(outputPin, HIGH);
      OCR1A = high1_us * 2;
      phase = 1;
      break;
    case 1:
      digitalWrite(outputPin, LOW);
      OCR1A = low_us * 2;
      phase = 2;
      break;
    case 2:
      digitalWrite(outputPin, HIGH);
      OCR1A = high2_us * 2;
      phase = 3;
      break;
    case 3:
      digitalWrite(outputPin, LOW);
      TCCR1B = 0;        // Остановить таймер
      TIMSK1 &= ~(1 << OCIE1A); // Отключить прерывания
      break;
  }
}



void setup() {
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);  
}



void loop() {
  startPulseSequence();
  delay(3000);
}
