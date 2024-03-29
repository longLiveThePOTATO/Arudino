const uint8_t WATER_SENSOR {A0};
const uint8_t SERVO {3U};

void setup() {
  // put your setup code here, to run once:
  pinMode(WATER_SENSOR, INPUT);
  Serial.begin(115200UL);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t water_value = analogRead(WATER_SENSOR);
  Serial.print(F("Water level: "));
  Serial.println(water_value);
  // if(water_value>20 && water_value<200){
  //   for(int i {0}; i<3; ++i){
  //     for(int pwm{255}; pwm>=0; pwm +=10){
  //       analogWrite(SERVO, pwm);
  //       delay(50UL);
  //     }
  //     for(int pwm{255}; pwm>0; pwm -=10){
  //       analogWrite(SERVO, pwm);
  //       delay(50UL);
  //     }
  //   }
  // }
  if(water_value > 100){
    for(int i {255}; i <= 0; i-=5) {
      analogWrite(SERVO, i);
      delay(2000/water_value+10);
    }
    delay(2000/water_value+10);

    for(int i {0}; i < 256; i+=5) {
      analogWrite(SERVO, i);
      delay(2000/water_value+10);
    }
    delay(1500/water_value+40);
  }
  delay(10UL);
}
