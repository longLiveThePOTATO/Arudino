#include <Arduino.h>
const uint8_t TS_PIN{31U};
const uint8_t LED_PIN{30U};
const uint8_t SW_PIN{29U};
const uint8_t BUZZ_PIN{28U};
const uint8_t DS_PIN{11U}, LATCH_PIN{12U}, CLOCK_PIN{13U};
static uint8_t count;

void setup() {
  // put your setup code here, to run once:
  pinMode(SW_PIN, INPUT);
  pinMode(TS_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  digitalWrite(LATCH_PIN, LOW); //잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, B10101010);
  digitalWrite(LATCH_PIN, HIGH);

  Serial.begin(115200UL);

  count = 0U;
  Serial.println(count);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool TS_state = digitalRead(TS_PIN);
  bool sw_state = digitalRead(SW_PIN);
  if(TS_state){
    count++;
    Serial.print(F("지진이 "));
    Serial. print(count);
    Serial.println(F("회 발생했습니다"));
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZ_PIN, 932, 1000);
  }
  else if(sw_state){
    count = 0U;
    Serial.print("리셋 ");
    Serial.println(count);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZ_PIN);
  }
  if(count == 0){
    
  digitalWrite(LATCH_PIN, LOW); //잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, B10101010);
  digitalWrite(LATCH_PIN, HIGH);
  }
  else{
    digitalWrite(LATCH_PIN, LOW); //잠그기
    shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, 1<<(count-1));
    digitalWrite(LATCH_PIN, HIGH);
  }
  delay(1000);
}
