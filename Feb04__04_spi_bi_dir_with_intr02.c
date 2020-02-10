#include "TM4C123xx.h"

uint16_t command[4] = {0x0002, 0x0002, 0x0003, 0x0003 };
__vo uint16_t recvcom[4] = {0,0,0,0};

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SPIStart(SSI3, SSI_Slave_Mode_OutEn, SSI_InterruptRxFIFO);
	SSIRecvWithIntr(SSI3, &recvcom[0], 64);
	while(1)
	{		
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

void SSI3_Handler(void)
{
	SSIIntrRecv(SSI3);
	//SSISendData(SSI3, command, 64);
}
