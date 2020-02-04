#include "TM4C123xx.h"

#define B1IsPressed				0x1			//	Command: Button 1 is pressed.					=>	Blink Green LED once.
#define B2IsPressed				0x2			//	Command: Button 2 is pressed.					=>	Blink Blue LED once.
#define BothArePressed		0x3			//	Command: Both buttons are pressed.		=>	Blink Red LED once.
#define NoButtonPressed		0x0			//	Command: No button is pressed.				=>	Make Red LED on.

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
	
	SPIStart(SSI3,SSI_Master_Mode,SSI_NoInterrupts);
	
	uint16_t command = 0;
	
	while(1)
	{
		command = ReadButtons2();						//	Read the state of buttons.
		
		SSISend(SSI3, command);
		switch(command)
		{
			case B1IsPressed:					TurnOff(LED_RED);
																blink(LED_GREEN);
																break;
			
			case B2IsPressed:					TurnOff(LED_RED);
																blink(LED_BLUE);
																break;
			
			case BothArePressed:			TurnOff(LED_RED);
																blink(LED_RED);
																break;
			
			case NoButtonPressed:			TurnOn(LED_RED);
																break;
		}
	}
	return 0;
}
