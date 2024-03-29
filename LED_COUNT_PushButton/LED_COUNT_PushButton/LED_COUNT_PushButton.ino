const uint8_t LED_PIN{31U};
const uint8_t BUTTON_SW{33U};
uint8_t count {0U};
bool button_state {false};

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_SW, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool is_pushed {digitalRead(BUTTON_SW)};
  delay(10UL);
  if(is_pushed){
    if(!button_state){
      button_state = true;
      ++count;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      Serial.println(String(F("Button counting: ")) + String(count));
      if(count > 65535) count = 0;
    }
  }
  else  button_state = false;
}
