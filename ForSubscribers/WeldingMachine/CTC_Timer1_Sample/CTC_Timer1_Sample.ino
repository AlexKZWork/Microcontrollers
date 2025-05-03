// Сдесь теперь не нужно указывать значение переменных
uint16_t pulse_high1 = 0;
uint16_t pulse_low = 0;
uint16_t pulse_high2 = 0;

volatile uint8_t phase = 0;
volatile bool sequenceActive = false;


void setup() {  
  DDRB |= (1 << DDB1);  // Устанавливаем бит 1 порта B как выход. Это вместо pinMode(9, OUTPUT)
}



// Вызываем эту функцию, чтобы начать последовательность, на вход подаются значения также в микросекундах. Ниже 10 мкс нельзя
void startPulseSequence(uint16_t high1_us, uint16_t low_us, uint16_t high2_us) {
  if (sequenceActive) return;  // Проверка, если последовательность еще не закончена то выход
  sequenceActive = true;

  pulse_high1 = high1_us;
  pulse_low   = low_us;
  pulse_high2 = high2_us;  

  cli();
  
  TCNT1 = 0;
  phase = 0; 

  TCCR1A = (1 << COM1A0);  // Именно это аппаратно переключит при совпадении с HIGH на LOW (и наоброт) , когда TCNT1 == OCR1A
  TCCR1B = (1 << WGM12) | (1 << CS11);

  TIMSK1 = (1 << OCIE1A);
  
  OCR1A = 10; // Для того чтобы таймер гарантированно отработал первое прерывание. Ниже задержку ставить нельзя. (По крайней мере все мои китайцы глючат если так не делать)
  sei();  
}



ISR(TIMER1_COMPA_vect) {
  phase++;  

  switch (phase) {
    case 1:      
      OCR1A = pulse_high1 * 2;      
      break;
    case 2:      
      OCR1A = pulse_low * 2;      
      break;
    case 3:      
      OCR1A = pulse_high2 * 2;
      break;
    case 4:
      TCCR1B = 0; // отключаем таймер      
      TCNT1 = 0;
      OCR1A = 0;
      TIMSK1 = 0;
      TCCR1A = 0;
      sequenceActive = false;  // Флаг завершения последовательности
      break;
  }
}



void loop() {
  startPulseSequence(80, 50, 170);  // Ниже 10 мкс. устанавливать нельзя
  delay(500);
}