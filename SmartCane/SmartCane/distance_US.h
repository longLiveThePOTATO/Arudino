
float distance_US(int a, int b){
  digitalWrite(a, HIGH);
  delayMicroseconds(2);
  digitalWrite(a, LOW);
  float duration = pulseIn(b, HIGH);
  float d = ((float)(340*duration)/10000)/2;    //cm 변환
  //float d = pulseIn(b, HIGH)*17/1000;
  return d;


  /*digitalWrite(a, LOW);
  digitalWrite(a, HIGH);              
  float d;
  float LowLevelTime = pulseIn(b, LOW) ;
  if (LowLevelTime <= 50000)              // the reading is invalid.
  {
    d = LowLevelTime / 50;
  }
  return d;*/

}

