#include <Arduino.h>
#include "Model.h"
#include "View.h"

// 모델 객체 생성
class Model model;
class View view;
const uint8_t SHUTDOWN_PIN {18};
const uint8_t SELECT_PIN {2};
const uint8_t NEXT_PIN {3};
volatile bool flagSD = false;
volatile bool flagS = false;
volatile bool flagN = false;

String UID;
String USER;
uint8_t countSelect {0};

void setup() {
  // 시리얼 통신 시작
  Serial.begin(115200);
  // 모델 초기화
  model.setup();
  // 컨트롤러 초기화
  attachInterrupt(digitalPinToInterrupt(SHUTDOWN_PIN), isShutDown, RISING);   //FALLING: high to low, RISING: low to high, CHANGE: high to low/low to high
  attachInterrupt(digitalPinToInterrupt(SELECT_PIN), isSEelect, CHANGE);   //FALLING: high to low, RISING: low to high, CHANGE: high to low/low to high
  attachInterrupt(digitalPinToInterrupt(NEXT_PIN), isNext, CHANGE);   //FALLING: high to low, RISING: low to high, CHANGE: high to low/low to high
  // 뷰 초기화
  view.setup();
  view.lcd.clear();
  view.printMessage("HM is  running...", 0);
    
}

void isShutDown(){
  flagSD = true;
}
void isSEelect(){
  flagS = true;
}
void isNext(){
  flagN = true;
}

void loop() {
  switch(countSelect) {
    case 0:
      if (flagS){
        flagS = false;
        ++countSelect;
      }
      // if(controller.countSelect()==1){
      //   ++countSelect;
      // }
      model.process();

      // 온도와 습도 값을 시리얼 모니터에 출력
      Serial.print("Temperature: ");
      Serial.print(model.getTemperature());
      Serial.print("°C, Humidity: ");
      Serial.print(model.getHumidity());
      Serial.println("%");
      Serial.println(model.getDistance());
      Serial.println(model.getDI());

      UID = model.readRFIDUID();
      USER = model.isRegistered(UID);

      if (model.isPersonDetected()) {
        view.printMSG("Person Detected", 1);
        view.printMSG("               ", 0);
        // RFID 카드 UID를 읽어옴
        if (!UID.equals("") && USER!= "") {
          Serial.println("사용자 확인: 문이 열립니다.");
          view.printMSG(USER+String(" Verified"), 0);
          view.printMSG("Gate open", 1);
          model.gateOpen();
          // 사용자 처리 코드 추가
        } else if(!UID.equals("")){
          Serial.println("미등록 사용자입니다.");
          view.printMessage("Verify failed", 0);
        }
      }else{
        view.lcd.clear();
        view.printMessage("HM is running...", 0);
      }
    
    break;  
     
  case 1:
    UID = model.readRFIDUID();
    USER = model.isRegistered(UID);
    view.printMessage("Tag to regist", 0);
    if (!UID.equals("") && USER == "") {   // RFID 카드 UID가 비어 있지 않고 등록된 사용자가 아닌 경우
      Serial.println("미등록 사용자입니다.");
      view.printMessage("Not Registed", 1);
      view.printMSG("Register?", 0);
      view.printMessage("1.Select  2.Skip", 1);
      if (flagS) {  // 선택 버튼이 눌린 경우
        ++countSelect;
        flagS = false;  // 플래그 초기화
        // model.registUser(UID);  // 사용자 등록
      } else if (flagN) {  // 스킵 버튼이 눌린 경우
        flagN = false;  // 플래그 초기화
        view.printMessage("Skip Regist", 1);  // "Skip Regist" 메시지 출력
        countSelect = 0;
      }
    } else if (!UID.equals("")) {  // 이미 등록된 사용자인 경우
      Serial.println("이미 등록된 사용자입니다.");
      view.printMSG("Already Registed", 0);
      view.printMessage(USER, 1);
      countSelect = 0;
      
      // if (flagS) {  // 선택 버튼이 눌린 경우
      //   countSelect = 0;
      //   flagS = false;  // 플래그 초기화
      //   // model.registUser(UID);  // 사용자 등록
      // } else if (flagN) {  // 스킵 버튼이 눌린 경우
      //   flagN = false;  // 플래그 초기화
      //   view.printMessage("Skip Regist", 1);  // "Skip Regist" 메시지 출력
      //   countSelect = 0;
      // }
    }
    flagS = false; // 해당 case의 동작이 끝났으므로 플래그 초기화
    flagN = false; // 해당 case의 동작이 끝났으므로 플래그 초기화
    break;

      
    case 2:
      if(model.registUser(UID) == true){ // 미등록 사용자를 등록
        view.printMessage("Register Success", 1);
        Serial.println(UID);
      } else {
        view.printMessage("Register failed", 1);
      }
      countSelect = 0;
      break;
  }
  Serial.println(String("countSelect: ") + countSelect);

  // 잠시 대기
  delay(100UL);
}
