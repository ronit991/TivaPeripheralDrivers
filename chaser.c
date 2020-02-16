#include "TM4C123xx.h"

void delay(void)
{
	for(unsigned int d = 0; d<500000; d++);
}

int main(void)
{
	UseLEDs();
	blink(LED_RED);
	DigitalPin(PB0, Output);
	DigitalPin(PB1, Output);
	DigitalPin(PB2, Output);
	DigitalPin(PB3, Output);
	DigitalPin(PB4, Output);
	DigitalPin(PB5, Output);
	DigitalPin(PB6, Output);
	DigitalPin(PB7, Output);
	
	GPIO_reg* pGPIOx = GPIO_B_P;
	uint8_t Reg = 1;
	while(1)
	{
		for(int i = 0; i<8; i++)
		{
			pGPIOx->GPIO_DATA_BITS[Reg] = 0xFF;
			Reg *= 2;
			delay();
		}
		Reg = 1;
		for(int i = 0; i<8; i++)
		{
			pGPIOx->GPIO_DATA_BITS[Reg] = 0x00;
			Reg *= 2;
			delay();
		}
		Reg = 1;
	}
	return 0;
}
