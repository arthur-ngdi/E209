#include <Arduino.h>

#define temp PIND&(0b00000100)
#define pressao PIND&(0b00001000)
#define nivel PIND&(0b00010000)
#define peso PIND&(0b00100000)
#define ligaLed PORTB|=0b00000100
#define desligaLed PORTB&=0b11111011

int main(){

  DDRB = 0b00000100;
  
  while(1){

    if((temp && pressao && nivel) || (~nivel && temp && peso) || (~nivel && ~temp && pressao) || (~nivel && ~peso && temp))
      ligaLed;
    else
      desligaLed;    
  }
}