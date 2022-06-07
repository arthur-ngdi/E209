#include <Arduino.h>



ISR(INT1_vect)
{

  if (EIMSK & (1 << INT0))
  {
    EIMSK &= ~(1 << INT0);
  }
  else
  {
    EIMSK |= (1 << INT0);
  }
}

ISR(INT0_vect)
{
  PORTD |= (1 << PD4);
  _delay_ms(1000);
  PORTD &= ~(1 << PD4);

}


int main()
{

  DDRD |= (1 << PD4) | (1 << PD5);
  EICRA |= (1 << ISC11) | (1 << ISC01) | (1 << ISC00);
  EIMSK |= (1 << INT0) | (1 << INT1);
  sei();

  while (1)
  {
    PORTD |= (1 << PD5);
    _delay_ms(500);
    PORTD &= ~(1 << PD5);
    _delay_ms(500);
  }
}
