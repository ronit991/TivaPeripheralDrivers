#include "TM4C123xx.h"
#include <string.h>

void blink(void);
void delay_s(void);
void delay_l(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	blink();
	
	SSIStart(SSI3,SSI_Slave_Mode_OutDis);
	uint16_t data[4];
	
	while(1)
	{
		SSIRecvData(SSI3, &data[0], 16);
		SSIRecvData(SSI3, &data[1], 16);
		SSIRecvData(SSI3, &data[2], 16);
		SSIRecvData(SSI3, &data[3], 16);
		
		
	}
	return 0;
}

/*****************************************************************************************************************/

void blink(void)
{
	WriteToPin(PF1,PIN_SET);			delay_s();
	WriteToPin(PF1,PIN_RESET);		delay_s();
}

void delay_s(void)
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<1000; j++);
}
void delay_l(void)
{
	for(int i = 0; i<50000; i++)
		for(int j = 0; j<1000; j++);
}
