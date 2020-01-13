#include "TM4C123xx.h"
#include <string.h>

void blink(void);
void delay_s(void);
void delay_l(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF2,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	WriteToPin(PF1,PIN_SET);
	delay_l();
	WriteToPin(PF1,PIN_RESET);
	
	SSIStart(SSI3,SSI_Master_Mode);
	char data[] = "ok";
	uint16_t length = strlen(data);
	SSISendData(SSI3,&length, 16);
	while(1)
	{
		SSISendData(SSI3,(uint16_t*)&data, length);
		
		blink();
	}
	return 0;
}

void blink(void)
{
	WriteToPin(PF3,PIN_SET);			delay_l();
	WriteToPin(PF3,PIN_RESET);		delay_l();
	WriteToPin(PF3,PIN_SET);			delay_l();
	WriteToPin(PF3,PIN_RESET);		delay_l();
	WriteToPin(PF2,PIN_SET);			delay_s();
	WriteToPin(PF2,PIN_RESET);		delay_l();
}

void delay_s(void)
{
	for(int i = 0; i<2000; i++)
		for(int j = 0; j<1000; j++);
}
void delay_l(void)
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<1000; j++);
}
