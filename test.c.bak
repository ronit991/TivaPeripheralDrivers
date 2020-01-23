#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"

void delay(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	
	WriteToPin(PF1,PIN_RESET);
	WriteToPin(PF3,PIN_RESET);
	
	uint8_t clockStatus = ((SYSCTL->RCC)>>4);
	clockStatus &= 0x03;
	
	if(clockStatus == 0x01)
		WriteToPin(PF3,PIN_SET);
	else
		WriteToPin(PF1,PIN_SET);
	
	while(1)
	{
	}
	return 0;
}

void delay(void)
{
	for(int i=0; i<5000; i++)
		for(int j=0; j<1000; j++)
		{
		}
}
