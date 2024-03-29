#include <avr/io.h>   //AVR chip memory 번지수 : PB0 ~ PB7 등등
#include <util/delay.h>   //delay 헤더 파일
#define F_CPU 16000000UL    //CPU Clock

int main(){
  //pinMode(13, HIGH); -> OUTPUT;
  //DDRx
  //PORT
  DDRB |= 0x80;    //pinMode(13, HIGH);   //0b1000000    //PORTB = PORTB | 0x80 (이중복합연산자)
  for(;;){    //무한루프 while(true)로도 표현 가능
    PORTB |= 0x80;
    _delay_ms(1000UL);
    PORTB &= ~0x80;
    _delay_ms(1000UL);
  }
  return 0;
}