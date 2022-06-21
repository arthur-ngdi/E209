#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#define FOSC 16000000U 
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

int tempo_sistema = 0;
int tempo_led = 0;
int tempo_botao = 0;
bool sistema_on = false;
bool controle_motor = false;
char msg_tx[20];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 1;
unsigned int valor = 0;

void UART_Transmit(char * dados)
{
	// Envia todos os caracteres do buffer dados ate chegar um final de linha
	while (*dados != 0)
	{
		while (!(UCSR0A & (1 << UDRE0))); // Aguarda a transmissão acabar
		// Escreve o caractere no registro de tranmissão
		UDR0 = *dados;
		// Passa para o próximo caractere do buffer dados
		dados++;
	}
}

ISR(USART_RX_vect)
{
	// Escreve o valor recebido pela UART na posição pos_msg_rx do buffer msg_rx
	msg_rx[pos_msg_rx++] = UDR0;
	if (pos_msg_rx == tamanho_msg_rx)
		pos_msg_rx = 0;
    if (msg_rx[0] == 'P' || msg_rx[0] == 'p')
    {
      int valor = OCR0A;
      char valor_OCR[8];
      //itoa(valor,valor_OCR,10);
      sprintf(valor_OCR,"%d",valor);
      UART_Transmit(valor_OCR);
      UART_Transmit("\n");
    }
    
}



ISR(INT0_vect)
{
  UART_Transmit("Sistema Desligado\n");
  tempo_sistema = 0;
  tempo_led = 0;
  tempo_botao = 0;
  sistema_on = false;
  controle_motor = false;
  PORTB &= ~(1 << PB1);
  OCR0A = 0;
}

ISR(TIMER2_OVF_vect)
{
  if (sistema_on == false)
  {
    if (!(PIND & (1 << PD4)))
    {
      if (tempo_botao == 306)
      {
        sistema_on = true;
        PORTB |= 1 << PB1;
        UART_Transmit("Sistema Ligado\n");
      }
      else
      {
        tempo_botao++;
      }
    }
    else
    {
      tempo_botao = 0;
    }
  }
  else
  {
    tempo_sistema++;
    tempo_led++;
    
    if (tempo_led == 245 && controle_motor == false)
    {
      PORTB &= ~(1 << PB1);
      controle_motor = true;
      tempo_sistema = 0;
    }

    if (tempo_sistema <= 1526 && controle_motor)
    {

      ADCSRA |= (1 << ADSC);
      while (ADCSRA == (ADCSRA | (1 << ADSC)))
        OCR0A = ADC * (255.0 / 1023.0);
    }
    else if (controle_motor)
    {
      OCR0A = 128;
    }
  }
}

void UART_Init(unsigned int ubrr)
{
	// Configura a baud rate */6
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	// Habilita a recepcao, tranmissao e interrupcao na recepcao */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	// Configura o formato da mensagem: 8 bits de dados e 1 bits de stop */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int main()
{
  DDRB = (1 << PB1);
  DDRD = 1 << PD6;
  PORTD = (1 << PD2) | (1 << PD4); // PULL-UP ATIVADO NOS PINOS 2 E 4;
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 = (1 << TOIE2);
  TCCR0A = (1 << COM0A1) | (1 << WGM00);
  TCCR0B = (1 << CS00);
  TCNT0 = 0;
  OCR0A = 0;
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); /*ADEN -> LIGA O ADC
                                                                     ADPSX -> CONFIGURA PRESCALER(111 == 128)*/
  EICRA = (1 << ISC01);
  EIMSK = (1 << INT0);
  sei();

  UART_Init(MYUBRR);

  while (1)
  {
  }
}