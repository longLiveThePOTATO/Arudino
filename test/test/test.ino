#include <Arduino.h>
const uint8_t TILT_SW{28U};
const uint8_t LED_PIN{29U};
const uint8_t BUTTON_SW{31U};
const uint8_t BUZZ_PIN{30U};
const uint8_t DS_PIN{11U}, LATCH_PIN{12U}, CLOCK_PIN{13U};
static uint8_t count;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_SW, INPUT);
  pinMode(TILT_SW, INPUT_PULLUP);
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
  bool ts_state = digitalRead(TILT_SW);
  bool sw_state = digitalRead(BUTTON_SW);
  if(ts_state){
    count++;
    digitalWrite(LED_PIN, HIGH);
    Serial.print(F("Richter Scale:  "));
    Serial. println(count);
    if(count >= 8){
      count = 8;
      tone(BUZZ_PIN, 932, 1000);
    }
  }
  else if(sw_state){
    count = 0U;
    Serial.print("리셋 ");
    Serial.println(count);
  }

  if(count == 0){
  digitalWrite(LATCH_PIN, LOW); //잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, 0);
  digitalWrite(LATCH_PIN, HIGH);
  }
  else{
    digitalWrite(LATCH_PIN, LOW); //잠그기
    shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, 1<<(count-1));
    digitalWrite(LATCH_PIN, HIGH);
  }
  delay(500);
}
