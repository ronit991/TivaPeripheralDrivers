#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"

void delay(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	
	WriteToPin(PF1,PIN_SET);
	WriteToPin(PF3,PIN_SET);

	
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
