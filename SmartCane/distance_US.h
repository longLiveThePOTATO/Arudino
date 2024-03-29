
float distance_US(int a, int b){
  digitalWrite(a, HIGH);
  delayMicroseconds(10);
  digitalWrite(a, LOW);
  float duration = pulseIn(b, HIGH);
  float d = ((float)(340*duration)/10000)/2;    //cm 변환_1
  //float d = pulseIn(b, HIGH)/58;   //cm 변환_2
  return d;

  //DFRobot 제공 데모 코드  ...정상측정 불가로 사용 중단
  /*digitalWrite(a, LOW);   //DFRobot 제공 데모 코드  ...정상측정 불가로 사용 중단
  digitalWrite(a, HIGH);              
  float d;
  float LowLevelTime = pulseIn(b, LOW) ;
  if (LowLevelTime <= 50000)              // the reading is invalid.
  {
    d = LowLevelTime / 50;
  }
  return d;*/
}





