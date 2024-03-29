#include "distance_US.h"
#include "pitches.h"


const int trigPin = 4;    //초음파센서_trig 핀
const int echoPin = 3;    //초음파센서_echo 핀
const int buzzerPin = 8;    //부저 핀
const int vibPin = 11;    //진동모터 핀

void setup() {
  // put your setup code here, to run once:
  //핀모드 지정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vibPin, OUTPUT);

  //시리얼 모니터 실행
  Serial.begin(9600);
  
}
//변수 초기화
float d1 = 0;   //직전에 측정한 거리
float d2 = 0;   //현재 측정한 거리


void loop() {
  // put your main code here, to run repeatedly:
  d1 = d2;    //d1에 직전 측정값 대입
  d2 = distance_US(trigPin, echoPin);   //d2에 현재 거리 측정값 대입

  //현재 측정한 거리 출력
  Serial.print("거리 = ");
  Serial.print(d2);
  Serial.println("cm");

  float dD = d1-d2;   //거리의 변화량
  dD = abs(dD);   //거리의 변화량_절대값
  int dT = d2*0.8 + 400;    //피드백 신호 간격

  if(d2>500){   //가측정 범위를 넘어선 경우 단순 지연
    delay(200);
  }
  else if(dD<500&&dD>120){    //거리의 변화량이 1.2m이상인 경우(갑자기 장애물이 나타나거나 주변 벽체가 사라진 경우)_길고 강한 피드백
    Serial.println(dD);
    analogWrite(vibPin, 160);
    tone(buzzerPin, 932, dT);
    delay(dT);
    analogWrite(vibPin, 0);
  
  }
  else if(dD<120)  {    //거리의 변화량이 1.2m이하인 경우(장애물 또는 벽체와의 거리가 점진적으로 변한 경우)_거리에 비례하는 간격으로 피드백
    tone(buzzerPin, NOTE_F3, 500);
    analogWrite(vibPin, 120);
    delay(dT);
    analogWrite(vibPin, 0);
  }


}
