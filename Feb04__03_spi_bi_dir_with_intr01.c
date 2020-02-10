#include "TM4C123xx.h"

uint16_t command[] = {0x0001, 0x0002, 0x0003, 0x0002 };

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SPIStart(SSI3, SSI_Master_Mode, SSI_NoInterrupts);
	
	uint16_t recvcom[4] = {0,0,0,0};
	
	while(1)
	{
		SSISendData(SSI3, command, 64);
		blink(LED_BLUE);
	}
	
	return 0;
}
