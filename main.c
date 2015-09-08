#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "5110.h"

#define F_CPU 8000000UL
const char* sGt_Tacho = "GT-TACHOMETER";
const char* sRevision= "1.0.0.0";

const char* sRpm = "RPM %i";
const char* sRps = "RPS %i";
const char* sMax = "MAX %i";
const char* sBlades = "Blades: %i";
char* message = 0;
volatile uint8_t blades = 2;
volatile uint16_t sig = 0;
volatile uint16_t rpm = 0;
volatile uint16_t rps = 0;
volatile uint16_t max = 0;
ISR(INT0_vect)
{
	/** check for blades button pressed **/
	if(++blades > 9){
		blades = 2;
	}
	_delay_us(500);
}
void setup();
int main(){
	setup();			/** setup stuff **/
	sei();
	lcd_clear();
	lcd_goto_xy(0, 0);
	lcd_str(sGt_Tacho);
	lcd_goto_xy(0, 3);
	lcd_str(sRevision);
	_delay_ms(2000);
	lcd_clear();
	while(1){
		/** print everything to the memory **/
		rpm = sig/blades;
		sprintf(message, sRpm, rpm);
		lcd_goto_xy(0, 0);
		lcd_str(message);

		rps = rpm/60;

		sprintf(message, sRps, rps);
		lcd_goto_xy(0, 1);
		lcd_str(message);


		sprintf(message, sMax, max);
		lcd_goto_xy(0, 2);
		lcd_str(message);


		sprintf(message, sBlades, blades);
		lcd_goto_xy(0, 3);
		lcd_str(message);
		sig+=100;
	}
	return 0;
}

void setup(){
	DDRD |= (1 << PD0);	/** Setup button input for blade change **/
	PORTD |= (1 << PD0);	/** Set Pull up **/
	/** setup lcd **/
	lcd_init(&PORTB, PB0, &PORTB, PB1, &PORTB, PB2, &PORTB, PB3, &PORTB, PB4);
	/** Like, take a fixed byte size from memory for displaying messages **/
	message = (char*) malloc(100);

	MCUCR &= ~(1 << ISC00);
	MCUCR |= (1 << ISC01);
	GICR |= (1 << INT0);



	//GIFR = (1 << INTF0) | (1 << INTF1);

}
