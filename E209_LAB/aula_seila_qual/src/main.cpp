#include <Arduino.h>

int main(){
  DDRD = 1<<PD6;

  TCCR0A = 0b10000001;
  TCCR0B = (1<<CS00);
  TCNT0 = 0;
  OCR0A = 0;

  ADMUX = (1<<REFS0);
  ADCSRA = 0b10000111;

  while(1){
    ADCSRA |= (1<<ADSC);

    while(ADCSRA == (ADCSRA | (1<<ADSC))){
      OCR0A = ADC*(255.0/1023.0);
    }
  }
  
}