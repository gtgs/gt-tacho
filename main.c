#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "5110.h"

const char* sGt_Tacho = "GT-TACHOMETER";
const char* sRevision= "1.0.0.0";

const char* sRpm = "RPM: %f";
const char* sRps = "RPS: %f";
const char* sMax = "MAX: %f";
const char* sBlades = "Blades: %f";
char* message = 0;
volatile uint8_t blades = 2;
volatile uint8_t rpm;

void setup();
int main(){
	setup();			/** setup stuff **/
	sei();				/** enable interrupts **/
	lcd_clear();
	lcd_goto_xy(0, 0);
	lcd_str(sGt_Tacho);
	lcd_goto_xy(0, 5);
	lcd_str(sRevision);
	_delay_ms(2000);
	while(1){
		/** print everything to the memory **/

		sprintf(message, sRpm, rpm);
		lcd_clear();
		lcd_goto_xy(0, 0);
		lcd_str(message);
		lcd_goto_xy(0, 10);
		lcd_str(sRpm);
		lcd_goto_xy(0, 10);
		lcd_str(sMax);
		lcd_goto_xy(0, 10);
		lcd_str(sBlades);

		/** check for blades button pressed **/
		if(1){//TODO: Replace with button pressed code
			if(++blades > 9){
				blades = 2;
			}
		}
	}
	return 0;
}

void setup(){
	/** Setup button input for blade change **/
	/** setup button for light **/
	/** setup pin change interrupt **/
	/** setup lcd **/
	lcd_init(&PORTB, PB0, &PORTB, PB1, &PORTB, PB2, &PORTB, PB3, &PORTB, PB4);
	/** Like, take a fixed byte size from memory for displaying messages **/
	message = (char*) malloc(100);

}
