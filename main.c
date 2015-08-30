#include <avr/io.h>
#include <avr/delay.h>
#include "5110.h"
void setup();
int main(){
	setup();
	while(1){
	}
	return 0;
}

void setup(){
	lcd_init(&PORTB, PB0, &PORTB, PB1, &PORTB, PB2, &PORTB, PB3, &PORTB, PB4);

}
