const uint8_t LED_HIGH {13};     // const uint8_t LED_PIN = 13U;
const uint8_t LED_LOW {12};

auto setup() -> void{
  // put your setup code here, to run once:
  pinMode(LED_HIGH, OUTPUT);       // REGISTER
  pinMode(LED_LOW, OUTPUT);
}

auto loop() -> void {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_HIGH, HIGH);
  digitalWrite(LED_LOW, HIGH);
  delay(250UL);       // delay(250);
  digitalWrite(LED_HIGH, LOW);
  digitalWrite(LED_LOW, LOW);
  delay(250UL);

}
