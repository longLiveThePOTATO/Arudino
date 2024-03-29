const uint8_t SW_PIN{29U};
const uint8_t LED_PIN{30U};
const uint8_t BUZZ_PIN{28U};
uint8_t RichterScale;
void setup() {
  // put your setup code here, to run once:
  pinMode(SW_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  Serial.begin(115200UL);
  Serial.println(RichterScale);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool sw_state = digitalRead(SW_PIN);
  if(sw_state){
    Serial.println(F("화재가 발생했습니다"));
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZ_PIN, 932);
  }
  else{
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZ_PIN);
  }


}
