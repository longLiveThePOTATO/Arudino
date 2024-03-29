enum PINS{
  PIR_SENSSOR, 35,
  BUZZ, 30,
  RED, 

  

}
bool pir_state {false};
uint16_t sensing_count {0u};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500UL);
  pinMode(PIR_SENSOR, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool detect = digitalRead(PIR_SENSOR);
  delay(10UL);
  if(digitalRead(PIR_SENSOR)){
    pir_state = true;
    Serial.println("Mom is comming!");

  }
  else{
    pir_state = false;
  }
}
