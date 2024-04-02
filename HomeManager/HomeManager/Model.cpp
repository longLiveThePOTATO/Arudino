// 모델 소스 파일 (model.cpp)
#include "model.h"

Model::Model() : dht(TEMP_HUMID_PIN, 11), ultraSonic(TRIG, ECHO), stepping(STEP_PER_REVOLUTION, 40, 38, 41, 39)  {
    // DHT 센서 초기화
    dht.begin();
}

void Model::setup() {
    // 각종 핀 모드 설정
    pinMode(TRIG, OUTPUT);    // 초음파 센서 TRIG 핀
    pinMode(ECHO, INPUT);     // 초음파 센서 ECHO 핀
    // RFID 모듈 초기화
    mfrc522.PCD_Init();
    MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
    stepping.setSpeed(14);    //RPM14
    
    
}

void Model::process() {
    // 온습도 센서 읽기
    bool dht11_state = dht.read();
    if (dht11_state) {
        temperature = dht.readTemperature();   // 온도 읽기
        humidity = dht.readHumidity();         // 습도 읽기
    }
    // 초음파 센서로부터 거리 측정
    distance = ultraSonic.measureDistanceCm(temperature);

}


float Model::getTemperature() {
    return temperature;
}

float Model::getHumidity() {
    return humidity;
}

float Model::getDistance() {
    return distance;
}

bool Model::isPersonDetected() {
    // 초음파 센서로부터 측정된 거리가 0부터 40 사이인지 확인하여 반환
    return (distance >= 0 && distance <= 40);
}

float Model::getDI() {
    // 불쾌지수 계산 함수
    return temperature - ((100 - humidity) / 5.0F);
}

String Model::readRFIDUID() {
    String UID = "";
    // 새로운 카드가 발견될 때까지 대기
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return UID; // 새로운 카드가 없으면 빈 문자열 반환
    }
    // 카드의 UID를 읽어옴
    if (!mfrc522.PICC_ReadCardSerial()) {
        return UID; // 카드 UID를 읽을 수 없으면 빈 문자열 반환
    }
    // 카드 UID를 문자열로 변환
    for (uint8_t i = 0u; i < 4; ++i) {
        UID += String(mfrc522.uid.uidByte[i], HEX);
    }
    // 대문자로 변환
    UID.toUpperCase();
    // 카드와의 통신 종료
    mfrc522.PICC_HaltA();
    // 변환된 UID를 반환
    return UID;
}
bool Model::registUser(String UID) {
    bool userRegistered = false; // 등록 여부 플래그
    // 등록되지 않은 사용자 찾기
    if(UID==""){
      return userRegistered;
    }
    for (int i = 0; i < 3; ++i) {
        if (users[i].uid == "") {
            // 사용자 등록
            users[i].uid = UID;
            users[i].name = "User" + String(i + 1);
            users[i].state = false; // 초기값 설정
            Serial.println(users[i].name + " 정보가 저장되었습니다.");
            userRegistered = true;
            return userRegistered; // 사용자 등록 성공
        }
    }
    return userRegistered; // 사용자 등록 실패

}

String Model::isRegistered(String UID) {
    for (int i = 0; i < 3; ++i) {
        if (users[i].uid == UID) {
            return users[i].name; // 등록된 사용자 발견
        }
    }
    return ""; // 등록된 사용자 없음
}
void Model::gateOpen() {
    Serial.println(F("Opening the gate..."));
    stepping.step(STEP_PER_REVOLUTION);
    delay(400);  // 회전이 완료될 때까지 대기
    stepping.step(-STEP_PER_REVOLUTION);
    delay(400);
}