void setup() {
  DDRB = 0b00000011;
}

void loop() {
  
  PORTB = 0b00000000;
  _delay_ms(500);
  
  PORTB |= 0b00000001;
  _delay_ms(500);
  
  PORTB = PORTB << 1;
  _delay_ms(500);
  
  PORTB |= 0b00000001;
  _delay_ms(500); 
  
//  PORTD &= 0b00000000;
//  _delay_ms(500);

}
