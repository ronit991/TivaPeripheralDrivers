#include "TM4C123xx.h"

#define B1IsPressed				0x1			//	Command: Button 1 is pressed.					=>	Blink Green LED once.
#define B2IsPressed				0x2			//	Command: Button 2 is pressed.					=>	Blink Green LED twice.
#define BothArePressed		0x3			//	Command: Both buttons are pressed.		=>	Blink Blue LED once.
#define NoButtonPressed		0x0			//	Command: No button is pressed.				=>	Make Red LED on.

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SSIStart(SSI3, SSI_Slave_Mode_OutDis, SSI_NoInterrupts);
	
	uint16_t	command = 0;
	
	while(1)
	{
		SSIRecv(SSI3, &command);
		
		switch(command)
		{
			case B1IsPressed:					TurnOff(LED_RED);
																blink(LED_GREEN);
																break;
			
			case B2IsPressed:					TurnOff(LED_RED);
																blink(LED_GREEN);
																blink(LED_GREEN);
																break;
			
			case BothArePressed:			TurnOff(LED_RED);
																blink(LED_BLUE);
																break;
			
			case NoButtonPressed:			TurnOn(LED_RED);
																break;
		}
	}
	return 0;
}
