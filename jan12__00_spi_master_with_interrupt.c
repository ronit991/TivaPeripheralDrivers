#include "TM4C123xx.h"
#include <string.h>

void blink(void);
void delay_s(void);
void delay_l(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	blink();
	
//	SSIStart(SSI0, SSI_Master_Mode, SSI_NoInterrupts);
//	SSIStart(SSI1, SSI_Master_Mode, SSI_InterruptTxFIFO);
	SSIStartK(SSI0,SSI_Master_Mode);
	SSIStartK(SSI3,SSI_Master_Mode);
	char data[] = "ok";
	uint16_t length = strlen(data);
	while(1)
	{
		SSISendData(SSI0, &length, length);
		delay_l();
		blink();
	}
	pSSI0->SSI_IM = 0;
	return 0;
}

/*****************************************************************************************************************/
void SSI0_Handler(void)
{
	uint8_t Interrupts = (uint8_t)(pSSI0->SSI_MIS & 0x0000000F);
	
	if(Interrupts & 0x01)				//	Receive overrun
	{
	}
	else if(Interrupts & 0x02)	//	Receive Timeout
	{
	}
	else if(Interrupts & 0x04)	//	Receive FIFO Half-Full or more
	{
		SSIIntrReceive(SSI0, SSI0_SS_PIN);
	}
	else if(Interrupts & 0x08)	//	Transmit FIFO Half-Full or less
	{
		SSIIntrSend(SSI0, SSI0_SS_PIN);
	}
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
