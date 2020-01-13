#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"


int main(void)
{
	GPIO_HANDLE led_zero;
	outpin(&led_zero,PF1,Digital,PullDn);
	WriteToPin(&led_zero,PIN_SET);
	
//	int pf3pinnum = getGPIOPinNumber(PF3);
//	GPIO_reg* PF3ADDR = getGPIOPortAddr(PF3,APB_BUS);
	
	while(1)
	{}
	return 0;
}
