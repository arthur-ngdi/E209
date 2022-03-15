#include <Arduino.h>

int main(){

  DDRD = 0b01100000;
  PORTD = 0b00000000;
  
  while(1){
    
    while(PIND & 0b00001000){
        PORTD&=0b00000000;
        PORTD|=0b01000000;
        _delay_ms(1000);
        PORTD&=0b00000000;
        PORTD|=0b00100000;
        _delay_ms(1000);
        PORTD&=0b00000000;
        PORTD|=0b01000000;
             
    }

    PORTD&=0b00000000;
    
    while(PIND & 0b00010000){
        PORTD&=0b00000000;
        PORTD|=0b01000000;
        _delay_ms(100);
        PORTD&=0b00000000;
        PORTD|=0b00100000;
        _delay_ms(100);
        PORTD&=0b00000000;
        PORTD|=0b01000000;
        
    }

  }
}

