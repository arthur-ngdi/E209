#include <Arduino.h>

char cont = 0;

ISR(INT0_vect){
  cont++;
  switch(cont){
    case 1:
      PORTD |= 1<<PD5;
      break;

    case 2:
      PORTD &=~ 1<<PD5;
      PORTD |= 1<<PD6;
      break;

    case 3:
      PORTD |= 1<<PD5;
      break;

    case 4:
      PORTD &=~ 1<<PD5;
      PORTD &=~ 1<<PD6;
      PORTD |= 1<<PD7;
      break;

    case 5:
      PORTD |= 1<<PD5;
      break;

    case 6:
      PORTD &=~ 1<<PD5;
      PORTD |= 1<<PD6;
      PORTD |= 1<<PD7;
      break;

    case 7:
      PORTD |= 1<<PD5;
      PORTD |= 1<<PD6;
      PORTD |= 1<<PD7;
      break;

    case 8:
      PORTD &=~ 1<<PD5;
      PORTD &=~ 1<<PD6;
      PORTD &=~ 1<<PD7;
      break;
  }
  
}

int main(){
  DDRD |= 1<<PD5 | 1<<PD6 | 1<<PD7;
  PORTD &=~ ((1<<PD5) | (1<<PD6) | (1<<PD7)); 
  EICRA |= 1<<ISC00 | 1<<ISC01;
  EIMSK = 1<<INT0;
  sei();


  while(1){

  }

}