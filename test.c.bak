#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"

void delay(void);

void blink_led(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	
	WriteToPin(PF3,PIN_SET);

	uint16_t data = 0x8;
	
	SSIInit2(SSI3,SSI_Master_Mode,SSI_Clk_SystemClock);
	while(1)
	{
		SSISendData(SSI3,&data,16);
		blink_led();
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


void blink_led(void)
{
	ToggleGPIOPin(PF1);			delay();
	ToggleGPIOPin(PF1);			delay();
	ToggleGPIOPin(PF1);			delay();
	ToggleGPIOPin(PF1);			delay();
}
