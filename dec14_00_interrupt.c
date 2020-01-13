#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"


#define PORTF_INTERRUPT_ADDRESS 0x000000B8

void clearICRreg(void);
void delay(void);
void blink(void);
void (*isr_func)(void);

GPIO_HANDLE led_zero;
GPIO_HANDLE led_one;
GPIO_HANDLE led_two;
GPIO_HANDLE button_zero;
GPIO_HANDLE button_one;

__vo int i = 0;

int main(void)
{
	outpin(&led_zero,PF1,Digital,PullDn);
	outpin(&led_one,PF2,Digital,PullDn);
	outpin(&led_two,PF3,Digital,PullDn);
	
	//interruptpin(&button_zero,PF4,blink,RisingEdge);
	
	interruptpin2(&button_zero,PF4,RisingEdge);
	//interruptpin2(&button_one,PF0,HighLevel);
	
	while(1)
	{
		WriteToPin(&led_zero,PIN_SET);
//		WriteToPin(&led_one,PIN_SET);
//		WriteToPin(&led_two,PIN_SET);
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

//void GPIOF_Handler(void)
//{
//	WriteToPin(&led_zero,PIN_RESET);
//	WriteToPin(&led_one,PIN_RESET);
//	WriteToPin(&led_two,PIN_RESET);
//	//for(i=0;i<10;i++)
//	//{
//		WriteToPin(&led_one,PIN_SET);
//		delay();
//		WriteToPin(&led_one,PIN_RESET);
//		delay();
//	//}
//	WriteToPin(&led_zero,PIN_SET);
//	WriteToPin(&led_one,PIN_SET);
//	WriteToPin(&led_two,PIN_SET);
//	i = 0;
//}


void GPIOF_Handler(void)
{
	WriteToPin(&led_two,PIN_SET);
	delay();
	WriteToPin(&led_two,PIN_RESET);
	delay();
	for(i=0;i<10;i++)
	{
		WriteToPin(&led_one,PIN_SET);
		delay();
		WriteToPin(&led_one,PIN_RESET);
		delay();
	}
	//Nvic->UNPEND[0] |= 1<<30;
	//Nvic->DIS[0] |= 1<<30;
	(&button_zero)->pGPIO->GPIO_ICR |= 1<<GPIOF_INT_PIN;
}

void blink(void)
{
	for(int i=0;i<10;i++)
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
	
}
