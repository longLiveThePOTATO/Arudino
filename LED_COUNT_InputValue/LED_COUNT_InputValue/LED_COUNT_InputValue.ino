const uint8_t DS_PIN{11U}, LATCH_PIN{12U}, CLOCK_PIN{13U};
const uint8_t CDS_PIN {A0};

void setup() {
  // put your setup code here, to run once:
  pinMode(CDS_PIN, INPUT);
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  Serial.begin(115200UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LATCH_PIN, LOW);

  uint16_t light_value {analogRead(CDS_PIN)};
  Serial.print(F("Light value: "));
  Serial.println(light_value);

  uint8_t light_sensor {map(light_value, 70, 400, 0, 255)};
  Serial.print(F("Light sensor: "));
  Serial.println(light_sensor);

  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, light_sensor);
  digitalWrite(LATCH_PIN, HIGH);

  delay(100UL);
}
