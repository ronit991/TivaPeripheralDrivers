#include "GPIO_PIN_NAMES.h"

GPIO_reg* getPortAddr(uint8_t pin, uint8_t bus)
{
	GPIO_reg* PortAddress;
	switch(pin)
	{
		case PA0:
		case PA1:
		case PA2:
		case PA3:
		case PA4:
		case PA5:
		case PA6:
		case PA7:	if(bus == AHB_BUS)	PortAddress = GPIO_A_H;
							else								PortAddress = GPIO_A_P;
							break;
		
		case PB0:
		case PB1:
		case PB2:
		case PB3:
		case PB4:
		case PB5:
		case PB6:
		case PB7:	if(bus == AHB_BUS)	PortAddress = GPIO_B_H;
							else								PortAddress = GPIO_B_P;
							break;
		
		case PC0:
		case PC1:
		case PC2:
		case PC3:
		case PC4:
		case PC5:
		case PC6:
		case PC7:	if(bus == AHB_BUS)	PortAddress = GPIO_C_H;
							else								PortAddress = GPIO_C_P;
		
		case PD0:
		case PD1:
		case PD2:
		case PD3:
		case PD4:
		case PD5:
		case PD6:
		case PD7:	if(bus == AHB_BUS)	PortAddress = GPIO_D_H;
							else								PortAddress = GPIO_D_P;
							break;
		
		case PE0:
		case PE1:
		case PE2:
		case PE3:
		case PE4:
		case PE5:
		case PE6:
		case PE7:	if(bus == AHB_BUS)	PortAddress = GPIO_E_H;
							else								PortAddress = GPIO_E_P;
							break;
		
		case PF0:
		case PF1:
		case PF2:
		case PF3:
		case PF4:
		case PF5:
		case PF6:
		case PF7:	if(bus == AHB_BUS)	PortAddress = GPIO_F_H;
							else								PortAddress = GPIO_F_P;
							break;
	}
	return PortAddress;
}


GPIO_reg* getPortAddrFromPortName(uint8_t GPIO_PORT, uint8_t bus)
{
	switch(bus)
	{
		case APB_BUS:	switch(GPIO_PORT)
									{
										case GPIO_PORT_A:		return GPIO_A_P;
										case GPIO_PORT_B:		return GPIO_B_P;
										case GPIO_PORT_C:		return GPIO_C_P;
										case GPIO_PORT_D:		return GPIO_D_P;
										case GPIO_PORT_E:		return GPIO_E_P;
										case GPIO_PORT_F:		return GPIO_F_P;
									}
		case AHB_BUS:	switch(GPIO_PORT)
									{
										case GPIO_PORT_A:		return GPIO_A_H;
										case GPIO_PORT_B:		return GPIO_B_H;
										case GPIO_PORT_C:		return GPIO_C_H;
										case GPIO_PORT_D:		return GPIO_D_H;
										case GPIO_PORT_E:		return GPIO_E_H;
										case GPIO_PORT_F:		return GPIO_F_H;
									}
	}
	//return GPIO_FP;
}


uint8_t getPinNumber(uint8_t pin)
{
	uint8_t pinNumber = 0;
	switch(pin)
	{
		case PA0:
		case PB0:
		case PC0:
		case PD0:
		case PE0:
		case PF0:	pinNumber = 0;
							break;

		case PA1:
		case PB1:
		case PC1:
		case PD1:
		case PE1:
		case PF1:	pinNumber = 1;
							break;

		case PA2:
		case PB2:
		case PC2:
		case PD2:
		case PE2:
		case PF2:	pinNumber = 2;
							break;

		case PA3:
		case PB3:
		case PC3:
		case PD3:
		case PE3:
		case PF3:	pinNumber = 3;
							break;

		case PA4:
		case PB4:
		case PC4:
		case PD4:
		case PE4:
		case PF4:	pinNumber = 4;
							break;

		case PA5:
		case PB5:
		case PC5:
		case PD5:
		case PE5:
		case PF5:	pinNumber = 5;
							break;

		case PA6:
		case PB6:
		case PC6:
		case PD6:
		case PE6:
		case PF6:	pinNumber = 6;
							break;

		case PA7:
		case PB7:
		case PC7:
		case PD7:
		case PE7:
		case PF7:	pinNumber = 7;
							break;
	}

	return pinNumber;
}

uint8_t getPortName(uint8_t pin)
{
	uint8_t PortName = 0;
	switch(pin)
	{
		case PA0:
		case PA1:
		case PA2:
		case PA3:
		case PA4:
		case PA5:
		case PA6:
		case PA7:	PortName = GPIO_PORT_A;
							break;
		case PB0:
		case PB1:
		case PB2:
		case PB3:
		case PB4:
		case PB5:
		case PB6:
		case PB7:	PortName = GPIO_PORT_B;
							break;
		case PC0:
		case PC1:
		case PC2:
		case PC3:
		case PC4:
		case PC5:
		case PC6:
		case PC7:	PortName = GPIO_PORT_C;
							break;
		case PD0:
		case PD1:
		case PD2:
		case PD3:
		case PD4:
		case PD5:
		case PD6:
		case PD7:	PortName = GPIO_PORT_D;
							break;
		case PE0:
		case PE1:
		case PE2:
		case PE3:
		case PE4:
		case PE5:
		case PE6:
		case PE7:	PortName = GPIO_PORT_E;
							break;
		case PF0:
		case PF1:
		case PF2:
		case PF3:
		case PF4:
		case PF5:
		case PF6:
		case PF7:	PortName = GPIO_PORT_F;
							break;
	}
	return PortName;
}

