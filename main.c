#include "hardware.h"
void setup();
int main(){
	while(1){
		_delay_ms(250);
		PORTB = ~PORTB;
	}
	return 0;
}

void setup(){
	DDRB = 0x10;
	PORTB |= 0x10;
}
