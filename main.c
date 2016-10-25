#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect) 
{ 
}

void UARTInit( void ) {
	UBRRL = 103;
	UBRRH = 0;
	UCSRA = 0;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;
}

void sendUART ( unsigned char c ) {
	while( !(UCSRA & (1 << UDRE))) {
	}
	UDR = c;
}


void greenHighlight( void ) {
	PORTD &= 0b01111111;
}

void yellowHighlight( void ) {
	PORTD &= 0b10111111;
}

void greenUnhighlight( void ) {
	PORTD |= 0b10000000;
}

void yellowUnhighlight( void ) {
	PORTD |= 0b01000000;
}
 
 

unsigned char readUART( void ) {
	while(!(UCSRA & (1 << RXC ))) {
	}
	return UDR; 
}	

 
int main( void ) {
	DDRA = 0b00000101; //конф как выходы
	DDRD = 0b11000000;
	unsigned char i;
	PORTA = 0x00;

	greenHighlight();
	yellowUnhighlight();
	unsigned char fine1=0;
	unsigned char fine2=0;
	
	while(1) {
		PORTA |= 1;
		_delay_ms( 100 );  
	  	i = PINA;
		if(!((1 << 1) & i)) {
			yellowHighlight();
			greenUnhighlight();
			fine1=0;
		}
		else {
			if(fine1 && fine2) 
				greenHighlight();
			fine1=1;
		}	
		_delay_ms( 100 );  		
		PORTA &= 0b11111110;
		_delay_ms( 100 );  
	  	i = PINA;
		if((1 << 1) & i) {
			yellowHighlight();
			greenUnhighlight();
			fine2=0;
		}
		else {
			if(fine1 && fine2)
				greenHighlight();						
			fine2=1;
		}
		_delay_ms( 100 );  
	}	
	return 0;
}
