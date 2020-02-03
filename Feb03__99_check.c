#include "TM4C123xx.h"

#define B1IsPressed				0x1			//	Command: Button 1 is pressed.					=>	Blink Green LED at slave once.
#define B2IsPressed				0x2			//	Command: Button 2 is pressed.					=>	Blink Green LED at slave twice.
#define BothArePressed		0x3			//	Command: Both buttons are pressed.		=>	Blink Blue LED at slave once.
#define NoButtonPressed		0x0			//	Command: No button is pressed.				=>	Make Red LED on at slave.

uint8_t ReadButtons2(void)
{
	uint8_t sw1 = !ReadFromPin(PA2);
	uint8_t sw2 = !ReadFromPin(PA3);
	if(sw1)
	{
		if(sw2)
			return 0x3;
		else
			return 0x1;
	}else if(sw2)
			return 0x2;
	return 0;
}


int main(void)
{
	UseLEDs();
	//UseButtons();
	DigitalPin(PA2,IN,PullUp);
	DigitalPin(PA3,IN,PullUp);
	
	blink(LED_RED);
	
	SSIStart(SSI3,SSI_Master_Mode,SSI_NoInterrupts);
	
	uint16_t buttons = 0;
	
	while(1)
	{
		buttons = ReadButtons2();						//	Read the state of buttons.
		
		SSISend(SSI3, buttons);
		
		blink(LED_GREEN);
	}
	return 0;
}