#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"

#define PF1 3

void outpin(int pin);

int main(void)
{
	GPIO_HANDLE led_zero;
	led_zero.pGPIO = GPIO_FP;
	led_zero.PIN_CONFIG.PinNumber = 2;
	led_zero.PIN_CONFIG.Direction = OUT;
	led_zero.PIN_CONFIG.UseAltFn = NO;
	led_zero.PIN_CONFIG.AltFn = 0;
	led_zero.PIN_CONFIG.DriveStrength = Eight_mA;
	led_zero.PIN_CONFIG.OutputType = PullUp;
	led_zero.PIN_CONFIG.PinMode = Digital;
	led_zero.PIN_CONFIG.Interrupt = 0;
	led_zero.PIN_CONFIG.isr_ptr = NULL;
	
	GPIO_Init(&led_zero);
	WriteToPin(&led_zero,PIN_SET);
	
	
	while(1)
	{}
	return 0;
}


//	uint8_t PinNumber;			//	This indicates the pin which we want to configure.
//	uint8_t Direction;			//	This is used to specify the direction of data flow (0: In,	1: Out).
//	uint8_t	UseAltFn;				//	Zero -> Use pin as GPIO. One -> Use pin in alternate fn mode.
//	uint8_t AltFn;					//	This is used to select one of the available alternate functions for a pin.
//	uint8_t DriveStrength;	//	This specifies the drive strength for the pin (2mA, 4mA, 8mA).
//	uint8_t OutputType;			//	This specifies whether the pin is working in Pull up/down or Open Drain Mode.
//	uint8_t PinMode;				//	This specifies whether the pin is working in digital or analog mode.
//	uint8_t Interrupt;			//	This is used to set the type, event, and mask for interrupt.
//	void (*isr_ptr)(void);

void outpin(int pin)
{
	switch(pin)
	{
		case 0:	break;
		case 1: break;
	}
}
