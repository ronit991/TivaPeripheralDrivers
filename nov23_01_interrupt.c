#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"


#define PORTF_INTERRUPT_ADDRESS 0x000000B8
#define PORTF_ISR_ADDRESS

void delay(void);
void isr_func(void);

GPIO_HANDLE led_zero;
GPIO_HANDLE led_one;


int main(void)
{
	outpin(&led_one,PF3,Digital,PullDn);
	outpin(&led_zero,PF1,Digital,PullDn);
	
	GPIO_HANDLE button_zero;
	inpin(&button_zero,PF4,Digital,PullUp);
	
	while(1)
	{
		WriteToPin(&led_zero,PIN_SET);
	}
	return 0;
}

void delay(void)
{
	for(int i=0; i<1000; i++)
		for(int j=0; j<1000; j++)
		{
		}
}

void isr_func(void)
{

		
		WriteToPin(&led_zero,PIN_SET);
		delay();
		WriteToPin(&led_zero,PIN_RESET);
		delay();
		WriteToPin(&led_one,PIN_SET);
		delay();
		WriteToPin(&led_one,PIN_RESET);
		delay();
}