#ifndef VIEW_H
#define VIEW_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class View {
public:
    void setup(); // 뷰 설정 메서드
    void printMessage(String message, int i); // 메시지 표시 메서드
    void printMSG(String message, int i);   // 메시지 표시 메서드
    // LCD_i2c 모니터 핀 번호
    LiquidCrystal_I2C lcd{0x27, 16, 2};    

private:
    // LED 핀 번호
    const uint8_t LED1 {11};
    const uint8_t LED2 {12};
    const uint8_t LED3 {13};

    // 부저 핀 번호
    const uint8_t BUZZER {5};

    // 경고등 핀 번호 (빨간 LED)
    const uint8_t WARNING_LED {7}; 

};

#endif // VIEW_H
