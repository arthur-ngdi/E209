#include <Arduino.h>

ISR(INT0_vect)
{
  if(OCR0A <= 225)
    OCR0A += 25;
  else OCR0A = 0; 
}

int main()
{
  DDRD |= 1 << PD6;
  Serial.begin(9600);
  EICRA |= 1 << ISC00 | 1 << ISC01;
  EIMSK |= 1 << INT0;
  TCCR0A |= 1 << WGM00 | 1 << WGM00 | 1 << COM0A1;
  TCCR0B |= 1 << CS00;
  OCR0A = 0;
  sei();

  while (1)
  {
    Serial.println(OCR0A);
    // if(OCR0A == 255) OCR0A = 0;
    // if (OCR0A == 250) OCR0A = 0;
  
  }
}