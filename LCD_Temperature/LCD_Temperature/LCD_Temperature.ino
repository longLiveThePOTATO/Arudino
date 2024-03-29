#include "DHT.h"
#include "HCSR04.h"
#include <LiquidCrystal_I2C.h>
enum ULTRASONIC{
  TRIG = 31UL,
  ECHO = A14
};
const uint8_t TEMP_HUMID_PIN {A9};
const uint8_t BUZZER {6U};
const uint8_t LED {13};
class DHT dht(TEMP_HUMID_PIN, 11);
class LiquidCrystal_I2C lcd(0x27, 16, 2);
class UltraSonicDistanceSensor ultra_sonic(TRIG, ECHO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL);
  dht.begin();
  lcd.init();
  lcd.home();
  lcd.backlight();

  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(dht.read()){
    float temperature = dht.readTemperature();
    lcd.print(temperature);
    float humidity = dht.readHumidity();
    lcd.setCursor(0, 1);
    lcd.print(humidity);
    delay(500UL);
    lcd.clear();
    lcd.setCursor(0, 0);

    Serial.println(String("Temperature: ") + temperature);
    float distance = ultra_sonic.measureDistanceCm(temperature);
    int dT = distance * 0.85 + 100;    //피드백 신호 간격

    if (distance > 400.0F or distance < 0.0F){
      Serial.println(F("Out of ranges"));
      Serial1.println(F("Out of ranges"));
      delay(50UL);
    }
    else if(distance < 200){
      Serial.print(F("Distance: "));
      Serial.println(distance + String("Cm"));
      Serial1.print(F("Distance: "));
      Serial1.println(distance + String("Cm"));
      Serial.println(dT);
      
      lcd.print("Welcome");
      tone(BUZZER, 622, dT);
      digitalWrite(13, HIGH);
      delay(dT);
      digitalWrite(13, LOW);
      delay(dT);
      lcd.clear();
      lcd.setCursor(0, 0);
    }
  }
}