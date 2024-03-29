#include "HCSR04.h"
enum ULTRASONIC{
  TRIG = 31UL,
  ECHO = 30UL
};
class UltraSonicDistanceSensor ultra_sonic(TRIG, ECHO);
float temperature {20};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = ultra_sonic.measureDistanceCm(temperature);
  if (distance > 400.0F or distance < 0.0F){
    Serial.println(F("Out of ranges"));
    Serial1.println(F("Out of ranges"));
  }
  else{
    Serial.print(F("Distance: "));
    Serial.println(distance + String("Cm"));
    Serial1.print(F("Distance: "));
    Serial1.println(distance + String("Cm"));
  }
  delay(50UL);
}
