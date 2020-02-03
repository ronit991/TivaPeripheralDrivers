#include "TM4C123xx.h"

#define SPI_COMMAND_1		51			//	Command: Button 1 is pressed.					=>	Blink Green LED at slave once.
#define SPI_COMMAND_2		52			//	Command: Button 2 is pressed.					=>	Blink Green LED at slave twice.
#define SPI_COMMAND_3		53			//	Command: Both buttons are pressed.		=>	Blink Blue LED at slave once.
#define SPI_COMMAND_4		54			//	Command: No button is pressed.				=>	Make Red LED on at slave.

#define B1IsPressed			0x1
#define B2IsPressed			0x2
#define BothArePressed	0x3

int main(void)
{
	UseLEDs();
	UseButtons();
	
	blink(LED_RED);
	
	SSIStart(SSI3,SSI_Master_Mode,SSI_NoInterrupts);
	
	uint16_t	command = 0;
	uint8_t buttons = 0;
	
	while(1)
	{
		buttons = ReadButtons();						//	Read the state of buttons.
		if(buttons != 0x0)
			blink(LED_GREEN);									//	Flash green led to acknowledge button read.
		
		// Send command corresponding to the buttons pressed.		
		switch(buttons)
		{
			case B1IsPressed:				command = SPI_COMMAND_1;			break;
			case B2IsPressed:				command = SPI_COMMAND_2;			break;
			case BothArePressed:		command = SPI_COMMAND_3;			break;
			default:								command = SPI_COMMAND_4;			break;
		}
		
		SSISendData(SSI3, &command, 16);
		
		blink(LED_RED);
		blink(LED_RED);
	}
	return 0;
}
