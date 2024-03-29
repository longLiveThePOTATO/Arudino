#include "distance_US.h"
#include "pitches.h"
#include "IDA.h"

const int trigPinF = 7;   //정면초음파센서_trig핀
const int echoPinF = 6;   //정면초음파센서_echo핀
const int trigPinL = 4;   //좌측초음파센서_trig핀
const int echoPinL = 5;   //좌측초음파센서_echo핀
const int trigPinR = 2;   //우측초음파센서_trig핀
const int echoPinR = 3;   //우측초음파센서_echo핀

const int buzzerPin = 8;    //부저
const int vibPin = 10;   //진동모터1
const int vibPin2 = 11;   //진동모터2

void setup() {
  // put your setup code here, to run once:
  //핀모드 지정
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(vibPin, OUTPUT);
  pinMode(vibPin2, OUTPUT);

  //시리얼 모니터 실행
  Serial.begin(9600);
  Serial.println("Start Measure");

  //아두이노 내장 led 점
  digitalWrite(13, HIGH);
}

float d1 = 0;   //직전에 측정한 거리
float dF; float dL; float dR; //현재 측정한 거리

void loop() {
  // put your main code here, to run repeatedly:

  d1 = dF;    //d1에 직전 측정값 대입
  dF = distance_US(trigPinF, echoPinF);   //dF에 현재 정면 거리 측정값 대입
  dL = distance_US(trigPinL, echoPinL);   //dL에 현재 좌측 거리 측정값 대입
  dR = distance_US(trigPinR, echoPinR);   //dR에 현재 우측 거리 측정값 대입

  //현재 측정한 거리 출력
  Serial.print("거리 = ");
  Serial.print(dF);
  Serial.println("cm");


  float dD = d1-dF;   //거리의 변화량
  dD = abs(dD);   //거리의 변화량_절대값
  int dT = d2*0.7 + 150;    //피드백 신호 간격
  Serial.println(dD);
  //delay(200);

  
  if (d2>500) {   //가측정 범위를 넘어선 경우 단순 지연
    digitalWrite(13, LOW);
    tone(buzzerPin, NOTE_GS2, 500);
    analogWrite(vibPin, 10);
    analogWrite(vibPin2, 20);
    Serial.println(" > 500");
    delay(300);
  }
  else if (dD<120){
    tone(buzzerPin, NOTE_F3, 500);
    analogWrite(vibPin, 130);
    analogWrite(vibPin2, 80);
    digitalWrite(13, HIGH);
    delay(dT+50);
    analogWrite(vibPin, 10);
    analogWrite(vibPin2, 5);
    digitalWrite(13, LOW);
    Serial.println("lower than 120");

  }
  else{
    Serial.println(dD);
    analogWrite(vibPin, 200);
    analogWrite(vibPin2, 150);
    digitalWrite(13, HIGH);
    tone(buzzerPin, NOTE_AS5, dT);
    delay(dT);
    digitalWrite(13, LOW);
    analogWrite(vibPin, 10);
    analogWrite(vibPin2, 5);
    Serial.println("higher than 120");

  }

}
