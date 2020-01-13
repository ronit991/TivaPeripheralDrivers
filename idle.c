#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"

int main(void)
{
	GPIO_HANDLE led_zero;
	GPIO_HANDLE led_one;
	GPIO_HANDLE led_two;
	
	outpin(&led_zero,PF1,Digital,PullDn);
	outpin(&led_one,PF2,Digital,PullDn);
	outpin(&led_two,PF3,Digital,PullDn);
	
	WriteToPin(&led_zero,PIN_SET);
	WriteToPin(&led_one,PIN_SET);
	WriteToPin(&led_two,PIN_SET);
	while(1)
	{
		//do nothing
	}
	return 1;
}
