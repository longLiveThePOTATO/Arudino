#include "View.h"

void View::setup() {
    lcd.init();
    lcd.home();
    lcd.backlight();
    printMessage("HOME MANAGER", 0);
    printMessage("START", 1);

    pinMode(LED1, OUTPUT); // LED 핀을 출력으로 설정합니다.
    pinMode(LED2, OUTPUT); // LED 핀을 출력으로 설정합니다.
    pinMode(LED3, OUTPUT); // LED 핀을 출력으로 설정합니다.
}

void View::printMessage(String message, int i) {
    lcd.setCursor(0, i); // 첫 번째 줄에 커서를 위치시킵니다.
    lcd.print("                "); // 16자의 공백 출력
    lcd.setCursor(0, i); // 첫 번째 줄에 커서를 위치시킵니다.
    lcd.print(message); // 메시지를 출력합니다.
    delay(500);
}

void View::printMSG(String message, int i) {
    lcd.setCursor(0, i); // 첫 번째 줄에 커서를 위치시킵니다.
    lcd.print("                "); // 16자의 공백 출력
    lcd.setCursor(0, i); // 첫 번째 줄에 커서를 위치시킵니다.
    lcd.print(message); // 메시지를 출력합니다.
}

// void View::warning(bool buzzer, bool warning_led){
//   if(warning_led == true){
//     digitalWrite(WARNING_LED, HIGH);
//   }
//   if (buzzer == true){
//     tone(BUZZER, 950, 200);
//   }
// }

// void View::setLED1(bool state){
//     digitalWrite(LED1, state);
// }