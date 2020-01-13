#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"

void delay(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF2,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	
	InterruptPin(PF4,RisingEdge);

	while(1)
	{
		WriteToPin(PF1,PIN_SET);
	}
	return 0;
}

void delay(void)
{
	for(int i=0; i<1000; i++)
		for(int j=0; j<1000; j++)
		{}
}

void GPIOF_Handler(void)
{
	WriteToPin(PF2,PIN_SET);
	delay();
	WriteToPin(PF2,PIN_RESET);
	delay();
	for(int i=0;i<10;i++)
	{
		ToggleGPIOPin(PF3);
		delay();
	}
	GPIO_reg* pGPIO = GPIO_F_P;
	pGPIO->GPIO_ICR |= 1<<GPIOF_INT_PIN;
}
void GPIOB_Handler(void)
{
	WriteToPin(PF2,PIN_SET);
	delay();
	WriteToPin(PF2,PIN_RESET);
	delay();
	for(int i=0;i<10;i++)
	{
		ToggleGPIOPin(PF3);
		delay();
	}
	GPIO_reg* pGPIO = GPIO_B_P;
	pGPIO->GPIO_ICR |= 1<<GPIOF_INT_PIN;
}

void GPIOA_Handler(void)
{
	WriteToPin(PF2,PIN_SET);
	delay();
	WriteToPin(PF2,PIN_RESET);
	delay();
	for(int i=0;i<10;i++)
	{
		ToggleGPIOPin(PF3);
		delay();
	}
	GPIO_reg* pGPIO = GPIO_A_P;
	pGPIO->GPIO_ICR |= 1<<GPIOF_INT_PIN;
}
