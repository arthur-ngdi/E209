#include <Arduino.h>

#define S1 PIND == (PIND&~(1<<PD3))
#define S2 PIND == (PIND&~(1<<PD4))

char estado = 'FECHADO';
bool pisca_pisca = false;

void piscaLed(bool pisca_pisca){
      if(pisca_pisca == true){
        PORTB |= 1<<PB1;
        _delay_ms(250);
        PORTB &=~ 1<<PB1;
        _delay_ms(250);
    }
}
   

ISR(INT0_vect){
  switch(estado)
  {

  case 'FECHADO':
    estado = 'ABRINDO';
    pisca_pisca = true;
    PORTB |= 1<<PB2;
    PORTB &=~ 1<<PB3;
    
    break;
  
  case 'ABRINDO':
    estado = 'PARADO_ABRINDO';
    pisca_pisca = true;
    PORTB &=~ 1<<PB2;
    PORTB &=~ 1<<PB3;
    
    break;

  case 'PARADO_ABRINDO':
    estado = 'FECHANDO';
    pisca_pisca = true;
    PORTB &=~ 1<<PB2;
    PORTB |= 1<<PB3;
    
    break;

  case 'FECHANDO':
    estado = 'PARADO_FECHANDO';
    pisca_pisca = true;
    PORTB &=~ 1<<PB2;
    PORTB &=~ 1<<PB3;
    
  case 'PARADO_FECHANDO':
    estado = 'ABRINDO';
    pisca_pisca = true;
    PORTB |= 1<<PB2;
    PORTB &=~ 1<<PB3;

  default:
    estado = 'PARADO_ABRINDO';
    pisca_pisca = true;
    PORTB &=~ 1<<PB2;
    PORTB &=~ 1<<PB3;

    break;
  }

}

int main(){

  DDRB |= 1<<PB1 | 1<<PB2 | 1<<PB3;
  PORTD |= 1<<PD3 | 1<<PD4;
  PORTB |= 1<<PB0;
  EICRA |= 1<<ISC01; 
  EIMSK |= 1<<INT0;
  sei();
  

  while(1){
    if(S1 && S2) estado = 'ABERTO';
      else if(S2) estado = 'FECHADO';
      piscaLed(pisca_pisca);

  }
}