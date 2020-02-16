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
	uint8_t Reg = 3;
	
	pGPIOx->GPIO_DATA = 0x01;			delay();
	pGPIOx->GPIO_DATA = 0x03;			delay();
	pGPIOx->GPIO_DATA = 0x06;			delay();
	pGPIOx->GPIO_DATA = 0x0C;			delay();
	pGPIOx->GPIO_DATA = 0x19;			delay();
	
	while(1)
	{
		pGPIOx->GPIO_DATA = 0x33;			delay();
		pGPIOx->GPIO_DATA = 0x66;			delay();
		pGPIOx->GPIO_DATA = 0xCC;			delay();
		pGPIOx->GPIO_DATA = 0x99;			delay();
	}
	return 0;
}
