# include "ledNum.h"
const uint8_t LEDS[] {6U, 7U, 8U, 9U, 10U, 11U, 12U, 13U};

void setup() {
  // put your setup code here, to run once:
  for(int i{0}; i<8; i++){
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i{0}; i<8; i++){
    digitalWrite(LEDS[i], HIGH);
    delay(1000);
  }
  for(int i{7}; i>=0; i--){
    digitalWrite(LEDS[i], LOW);
    delay(1000);
  }
}
