#include <Arduino.h>

int cont_ms  = 0;
int cont_s = 0;
int cont_min = 0;

ISR(TIMER2_OVF_vect){

  //Serial.println(TCNT2);
  cont_s++;
  if(cont_s >= 60){
    cont_ms++;
    PORTD |= 1<<PD3;
    if(cont_ms >= 6){
      PORTD &=~ 1<<PD3;
      cont_ms = 0;
      cont_s = 0;
    }
    if(cont_ms == 1) {
      cont_min++;
    }
    if(cont_min>=60){
      cont_ms++;
      PORTD |= 1<<PD4;
      if(cont_ms >= 6){
        PORTD &=~ 1<<PD4;
        cont_ms = 0;
        cont_min = 0;
      }
    }
      
  }

}

int main(){

  DDRD |= 1<<PD3 | 1<<PD4;
  TCCR2B |= 1<<CS22 | 1<<CS21 | 1<<CS20 | 1<<WGM22;
  TIMSK2 |= 1<<TOIE2;
  sei();
  

  while(1){
    
  }
}