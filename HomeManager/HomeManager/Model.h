#ifndef MODEL_H
#define MODEL_H

#include <Arduino.h>
#include <MFRC522Debug.h> 
#include <MFRC522DriverPinSimple.h> 
#include <MFRC522DriverSPI.h>  
#include <MFRC522v2.h>
#include <Stepper.h>
#include "HCSR04.h"
#include "DHT.h"

// 사용자 정보 구조체 정의
struct UserInfo {
  String name;      // 사용자명
  String uid;       // UID
  bool state;    // 입실 여부
};

// 모델 클래스 정의
class Model {
public:
    Model();
    void setup();
    void process();
    bool isPersonDetected();
    float getTemperature();  
    float getHumidity();
    float getDistance();
    float getDI(); // 불쾌지수 반환 함수
    String readRFIDUID(); // RFID 카드 UID를 읽는 함수
    bool registUser(String UID); // 사용자 등록 함수
    String isRegistered(String UID); // 등록된 사용자인지 확인하는 함수
    void gateOpen();
private:
    // 핀 정의
    enum ULTRASONIC {   //  초음파 센서 핀
        TRIG = 31UL,
        ECHO = 30UL
    };
    // const uint8_t SERVO {41};  // 서보모터 제어 핀
    const uint8_t TEMP_HUMID_PIN {A9};   // 온습도 센서 데이터 핀
    MFRC522DriverPinSimple sda_pin{53};
    MFRC522DriverSPI driver{sda_pin};
    MFRC522 mfrc522{driver};

    DHT dht; // DHT 센서 객체
    UltraSonicDistanceSensor ultraSonic;   // 초음파 센서 객체
    const uint16_t STEP_PER_REVOLUTION {1024U};   //32(1바퀴) * 64(기어비)
    Stepper stepping;   //PIN_NUMBER;
    float temperature;   // 온도 값
    float humidity;   // 습도 값
    float distance;   // 거리 값

    
    // 사용자 정보 배열 선언
    UserInfo users[3];
};

#endif    // MODEL_H
