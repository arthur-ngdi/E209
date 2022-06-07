#include <Arduino.h>

ISR(PCINT0_vect){

  PORTD |= (1<<PD7);
  _delay_ms(1000);
  PORTD &=~ (1<<PD7);
  
}

ISR(PCINT1_vect){

  PORTD |= (1<<PD6);
  _delay_ms(500);
  PORTD &=~ (1<<PD6);
  
}

ISR(PCINT2_vect){
  
  PORTB |= (1<<PB1);
  _delay_ms(2000);
  PORTB &=~ (1<<PB1);

}

int main(){

  DDRD |= (1<<PD5) | (1<<PD6) | (1<<PD7);
  DDRB |= (1<<PB1);
  PCICR |= 0b00000111;
  PCMSK0 |= 0b00010000;
  PCMSK1 |= 0b00010000;
  PCMSK2 |= 0b00010000;
  sei();

  while(1){

    PORTD |= (1<<PD5);
    _delay_ms(250);
    PORTD &=~ (1<<PD5);
    _delay_ms(250);

  }
}