#include <avr/io.h>   //AVR chip memory 번지수 : PB0 ~ PB7 등등
#include <util/delay.h>   //delay 헤더 파일
#define F_CPU 16000000UL    //CPU Clock

int main(){
  //pinMode(13, HIGH); -> OUTPUT;
  //DDRx
  //PORT
  DDRB |= 0x80;    //pinMode(13, HIGH);   //0b1000000    //PORTB = PORTB | 0x80 (이중복합연산자)
  //DDRE = ~0x20;   //0b0010000;   //PE5 -> 0    //pinMode(3, LOW);
  for(;;){    //무한루프 while(true)로도 표현 가능
    uint8_t button_state = PINE & 0x20;   //0b0010 0000
    if(button_state){
      PORTB |= 0x80;
    }
    else{
      PORTB &= ~0x80;
    }
  }
  return 0;
}