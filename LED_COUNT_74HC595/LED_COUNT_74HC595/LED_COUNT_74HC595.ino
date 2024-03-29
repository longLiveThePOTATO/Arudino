const uint8_t DS_PIN{11U}, LATCH_PIN{12U}, CLOCK_PIN{13U};
const uint8_t VR_PIN{A15};

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  digitalWrite(LATCH_PIN, LOW); //잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, B10101010);
  digitalWrite(LATCH_PIN, HIGH);
  pinMode(VR_PIN, INPUT); //생략 가능
  Serial.begin(115200UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  //LATCH 걸쇠 걸기
  uint16_t vr_value {analogRead(VR_PIN)};
  Serial.println(vr_value);
  uint16_t mapped_value {map(vr_value, 0, 1018, 0, 255)};
  Serial.print(F("Mapped value: "));
  Serial.println(mapped_value);
  digitalWrite(LATCH_PIN, LOW); //잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, mapped_value);
  digitalWrite(LATCH_PIN, HIGH);
}
