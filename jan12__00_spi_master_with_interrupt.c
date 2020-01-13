#include "TM4C123xx.h"
#include <string.h>

void blink(void);
void delay_s(void);
void delay_l(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	blink();
	
	SSIStart(SSI0, SSI_Master_Mode, SSI_NoInterrupts);
	SSIStart(SSI0,SSI_Master_Mode,SSI_InterruptTxFIFO);
	char data[] = "ok";
	uint16_t length = strlen(data);
	while(1)
	{
		SSISendData(SSI0, &length, length);
		delay_l();
		blink();
	}
	return 0;
}

/*****************************************************************************************************************/
void SSI0_Handler(void)
{
	
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
