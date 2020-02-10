#include "TM4C123xx.h"

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SPIStart(SSI3, SSI_Master_Mode, SSI_NoInterrupts);
	
	uint16_t command[] = {0x0001, 0x0002, 0x0003, 0x0002 };
	uint16_t recvcom[4] = {0,0,0,0};
	
	while(1)
	{
		SSISendData(SSI3, command, 64);
		SSIRecvData(SSI3, recvcom, 64);
		
		for( int i = 0; i<4; i++)
			switch(recvcom[i])
			{
				case 1:		WhiteLEDoff();
									blink(LED_GREEN);
									break;
			
				case 2:		WhiteLEDoff();
									blink(LED_BLUE);
									break;
			
				case 3:		WhiteLEDoff();
									blink(LED_RED);
									break;
			
				case 0:		TurnOn(LED_RED);
									break;
				
				default:	WhiteLEDon();
			}
	}
	
	return 0;
}
