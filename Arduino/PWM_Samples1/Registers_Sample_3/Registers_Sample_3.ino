// ШИМ 10 пин

void setup() {
  pinMode(10, OUTPUT);  
  TCCR1A = (1 << COM1B1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  ICR1 = 99;  
}

void loop() {
  for (int i = 0; i < 99; i++) {
    OCR1B = i;
    delay(10);
  }
}
