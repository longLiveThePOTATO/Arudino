const uint8_t digits[] {26, 27, 23, 24, 25, 28, 29, 22};
const uint8_t digit0[] {1, 1, 1, 1, 1, 1, 0, 0};
const uint8_t digit1[] {1, 0, 0, 1, 1, 1, 1, 1};
const uint8_t digit2[] {1, 1, 0, 1, 1, 0, 1, 0};
const uint8_t digit3[] {0, 0, 0, 0, 0, 0, 1, 0};
const uint8_t digit4[] {0, 0, 0, 0, 0, 0, 0, 1};
const uint8_t digit5[] {0, 0, 0, 0, 0, 0, 1, 1};


void setup() {
  // put your setup code here, to run once:
  for(auto digit : digits){
    pinMode(digit, OUTPUT);
  }
  digitalWrite(digits[0], 1);
  digitalWrite(digits[1], HIGH);
  digitalWrite(digits[2], HIGH);
  digitalWrite(digits[3], HIGH);
  digitalWrite(digits[4], HIGH);
  digitalWrite(digits[5], HIGH);
  digitalWrite(digits[6], 0);
  digitalWrite(digits[7], LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
