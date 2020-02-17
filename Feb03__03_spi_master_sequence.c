#include "TM4C123xx.h"
#define B1IsPressed				0x1			//	Command: Button 1 is pressed.					=>	Blink Green LED once.
#define B2IsPressed				0x2			//	Command: Button 2 is pressed.					=>	Blink Blue LED once.
#define BothArePressed		0x3			//	Command: Both buttons are pressed.		=>	Blink Red LED once.
#define NoButtonPressed		0x0			//	Command: No button is pressed.				=>	Make Red LED on.
int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SPIStart(SSI3, SSI_Master_Mode, SSI_NoInterrupts);
	
	uint16_t command[] = {0x0001, 0x0002, 0x0003, 0x0002 };
	
	while(1)
	{
		SSISendData(SSI3, command, 64);
		blink(LED_GREEN);
	}
	
	return 0;
}