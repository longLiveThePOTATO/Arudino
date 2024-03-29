const uint8_t SERVO {3U};
void setup() {
  // put your setup code here, to run once:
  pinMode(SERVO, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i {0}; i < 256; i+=10) {
    analogWrite(SERVO, i);
    delay(50UL);
  }
  delay(1000UL);
  for(int i {255}; i <= 0; i-=10) {
    analogWrite(SERVO, i);
    delay(50UL);
  }
  delay(1000UL);
}
