#include <Arduino.h>

bool flag = false;
bool acende_led = false;
int cont = 0;


ISR(INT0_vect){

  flag = !flag;
  if(flag){
    TCNT0 = 0;
  }else{
      PORTD |= 1<<PD3;
      
      PORTD &=~ 1<<PD3;
      
      cont = 0;
  }   
}

 ISR(TIMER0_COMPA_vect){
   if(flag){
     cont++;
   }else if cont = 0{

   }
 }

int main(){

  DDRD |= 1<<PD3;
  EICRA  |= 1<<ISC00;
  TCCR0B |= 1<<CS02 | 1<<CS00;
  TCCR0A |= 1<<WGM01;
  OCR0A = 16;
  TIMSK0 |= 1<<OCIE0A;
  sei();


  while(1){
    if(acende_l#include <Arduino.h>

bool flag = false;
bool acende_led = false;
int cont = 0;


ISR(INT0_vect){

  flag = !flag;
  if(flag){
    TCNT0 = 0;
  }else{
      PORTD |= 1<<PD3;
      
      PORTD &=~ 1<<PD3;
      
      cont = 0;
  }   
}

 ISR(TIMER0_COMPA_vect){
   if(flag){
     cont++;
   }else if cont = 0{
ed){
  
    }
  }
    

}