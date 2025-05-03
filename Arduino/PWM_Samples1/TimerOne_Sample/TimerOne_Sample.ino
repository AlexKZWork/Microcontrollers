#include <TimerOne.h>

#define PWM_PIN 10

void setup() {
  Timer1.initialize(1); // 1 мкс = 1 MHz 
}

void loop() {
  Timer1.setPeriod(10); // 10 мкс = 100 kHz
  Timer1.pwm(PWM_PIN, 512); // 50%
  delay(3000);

  Timer1.setPeriod(4); // 4 мкс = 250 kHz
  Timer1.pwm(PWM_PIN, 256); // 25%
  delay(3000);

  Timer1.setPeriod(2); // 2 мкс = 500 kHz
  Timer1.pwm(PWM_PIN, 128); // 12.5%
  delay(3000);
  
  Timer1.setPeriod(1); // 1 мкс = 1 MHz
  Timer1.pwm(PWM_PIN, 768); // 75%
  delay(3000);
}
