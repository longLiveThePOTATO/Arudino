const uint8_t VR_PIN{A0};
const uint8_t LEDS[] {6U, 7U, 8U, 9U, 10U, 11U, 12U, 13U};

void setup() {
  // put your setup code here, to run once:
  pinMode(VR_PIN, INPUT); //생략 가능
  for(int i{0}; i<8; i++){
    pinMode(LEDS[i], OUTPUT);
  }
  Serial.begin(115200UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t vr_value {analogRead(VR_PIN)};
  Serial.println(vr_value);
  uint16_t mapped_value {map(vr_value, 0, 902, 0, 8)};
  Serial.print(F("Mapped value: "));
  Serial.println(mapped_value);
  for(int i{0}; i<mapped_value; i++){
    digitalWrite(LEDS[i], HIGH);
  }
  for(int i{mapped_value}; i<8; i++){
    digitalWrite(LEDS[i], LOW);
  }
  delay(10UL); //생략 가능
}
