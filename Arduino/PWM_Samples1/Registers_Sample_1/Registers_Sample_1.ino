// ШИМ 9 пин

void setup() {
  pinMode(9, OUTPUT);  
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  ICR1 = 1;
  OCR1A = 0;
}

void loop() {
}