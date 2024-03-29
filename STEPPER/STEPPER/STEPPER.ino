#include <Stepper.h>
const uint16_t STEP_PER_REVOLUTION {2048U};   //32(1바퀴) * 64(기어비)
class Stepper stepping(STEP_PER_REVOLUTION, 6, 8, 7, 9);   //PIN_NUMBER;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  stepping.setSpeed(14);    //RPM14
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Clockwise"));
  stepping.step(STEP_PER_REVOLUTION);
  delay(1000UL);
  Serial.println(F("Counter Clockwise"));
  stepping.step(-STEP_PER_REVOLUTION);
  delay(1000UL);
}
