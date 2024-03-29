const uint8_t RELAY_SW {2U};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);   //시리얼 모니터
  Serial1.begin(9600UL);    //블루투스
  Serial1.println("블루투스 리셋");
  pinMode(RELAY_SW, OUTPUT);    //릴레이 스위치
  digitalWrite(RELAY_SW, HIGH);


}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()){
    Serial1.println("Hello");
    char input_value = static_cast<char>(Serial1.read());   //1byte 읽어서 아스키 코드로 변환
    if(input_value == '1'){
      digitalWrite(RELAY_SW, HIGH);
      Serial1.println(F("Switch on"));
    }
    else if(input_value == '0'){
      digitalWrite(RELAY_SW, LOW);
      Serial1.println(F("Switch off"));
    }
    else{
      Serial1.println(F("신호 입력 대기"));
    }
  }
  delay(1000);
}
