#include "DHT.h"
const uint8_t TEMP_HUMID_PIN {A9};
const uint8_t FIRE_SENSOR {3U};   //interrupt pin3 => PULL-DOUWN S/W
const uint8_t RELAY_SW {13U};
class DHT dht(TEMP_HUMID_PIN, 11);
volatile uint16_t button_count {0U};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL);
  pinMode(RELAY_SW, OUTPUT);
  dht.begin();
  Serial1.println("Bluetooth is ready");
  //attachInterrupt(digitalPinToInterrupt(FIRE_SENSOR), call911, RISING);   //FALLING: high to low, RISING: low to high, CHANGE: high to low/low to high
}

// void call911(){
//   ++button_count;
//   digitalWrite(RELAY_SW, LOW);
//   analogWrite(TEMP_HUMID_PIN, LOW);
//   for(int i = 0; i < 3; i++){
//     Serial.println(F("FIRE!! Call 911"));
//     Serial.println(button_count);
//     Serial1.println(F("FIRE!! Call 911"));
//   }
// }

void loop() {
  // put your main code here, to run repeatedly:
  bool dht11_state {dht.read()};
  if(dht11_state){
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    Serial.print(F("온도: "));
    Serial.println(String(temperature)+String("°C"));
    Serial1.print(F("온도: "));
    Serial1.println(String(temperature)+String("°C"));
    Serial.print(F("습도: "));
    Serial1.println(String(humidity)+String("%"));
    Serial1.print(F("습도: "));
    Serial.println(String(humidity)+String("%"));
    float heat = dht.computeHeatIndex(temperature, humidity);
    Serial.print(F("열: "));
    Serial.println(String(heat)+String(" degree"));
    Serial1.print(F("열: "));
    Serial1.println(String(heat)+String(" degree"));
    if(heat >= 18){
      digitalWrite(RELAY_SW, HIGH);
      Serial.println("환기 시작");
      Serial1.println("환기 시작");
    }
    else{
      digitalWrite(RELAY_SW, LOW);
      Serial.println("환기 종료");
      Serial1.println("환기 종료");
    }
    delay(500);
  }
}
