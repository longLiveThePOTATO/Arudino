#include <IRremote.hpp>
const uint8_t IR_PIN {11U};
class IRrecv irrecv(IR_PIN);
class decode_result;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  irrecv.begin(IR_PIN, LED_BUILTIN);
  Serial.begin(115200UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode()){
    uint8_t data_value = irrecv.decodedIRData.command;
    Serial.println(data_value, HEX);    //16진수로 출력
    switch(data_value){
      case 0x16:
        digitalWrite(LED_BUILTIN, HIGH);
        break;
      case 0x0C:
        digitalWrite(LED_BUILTIN, LOW);
        break;
    }
    irrecv.resume();
    irrecv.start(10);     //0.001
  }
}
