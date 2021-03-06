/******************************************************************************************************************
*	@file			-	GPIO_PINS.c																																													*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
* This file contains definitions of functions declared in GPIO_PINS.h file.																				*
*																																																									*
* @Note			-	ReadButtons() function is not working properly (see section 3). This needs a diagnosis.							*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/


#include "GPIO_PINS.h"



/******************************************************************************************************************
*	Section 2: Pin number & Address resolver functions																															*
*																																																									*
*	@getPortAddr()		-	Get pointer to a GPIO port using name of a pin or port.																			*
* @getPortName()		-	Get port name for a given pin.																															*
*	@getPinNumber()		-	Get pin number(i.e. 3 for PF3, 7 for PA7 etc.) of a pin.																		*
******************************************************************************************************************/



/******************************************************************************************************************
* @getPortAddr()																																																	*
* @brief	-	Get module access pointer to a GPIO port using name of a pin or port.																	*
* @pin		-	Pin name or GPIO port, whose address (access pointer) is needed.																			*
* @bus		-	APB/AHB Bus.																																													*
* @return	- Module access pointer to a GPIO port.																																	*
*																																																									*
* @Note		- If an incorrect pin_name or port_name is given as an input to this function, it returns the pointer 	*
*						to GPIO Port A connected over AHB Bus.																																*
******************************************************************************************************************/
GPIO_reg* getPortAddr(uint8_t pin, uint8_t bus)
{
	GPIO_reg* PortAddress;
	switch(pin)
	{
		case GPIO_PORT_A:
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
		
		case GPIO_PORT_B:
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
		
		case GPIO_PORT_C:
		case PC0:
		case PC1:
		case PC2:
		case PC3:
		case PC4:
		case PC5:
		case PC6:
		case PC7:	if(bus == AHB_BUS)	PortAddress = GPIO_C_H;
							else								PortAddress = GPIO_C_P;
		
		case GPIO_PORT_D:
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
		
		case GPIO_PORT_E:
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
		
		case GPIO_PORT_F:
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
		
		default:	PortAddress = GPIO_A_H;
	}
	return PortAddress;
}



/******************************************************************************************************************
* @getPortName()																																																	*
* @brief	-	Get GPIO port name for a given pin.																																		*
* @pin		-	GPIO pin, whose port name is needed.																																	*
* 																																																								*
* @return	- GPIO port name for the given pin. If an incorrect pin_name is given as an input to this function, it	*
*						returns GPIO_PORT_A. In case an unwanted behaviour is observed, check for name mismatch.							*
******************************************************************************************************************/
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
		
		default:	PortName = GPIO_PORT_A;
	}
	return PortName;
}



/******************************************************************************************************************
* @getPinNumber()																																																	*
* @brief	-	Get Pin Number of a given pin.																																				*
* @pin		-	GPIO pin, whose Pin Number is required.																																*
* 																																																								*
* @return	- Pin Number of the given pin. If an incorrect pin_name is given as an input to this function, it				*
*						returns 0. In case an unwanted behaviour is observed, check for name mismatch.												*
******************************************************************************************************************/
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



/******************************************************************************************************************
*	Section 3: Functions for on-board LEDs and Buttons:																															*
*																																																									*
*	@UseLEDs()			-	Initialize on-board LEDs as Output pins.																											*
*	@TurnOn()				-	Turn On an LED ( use this instead of WriteToPin() function for better readability. )					*
*	@TurnOff()			-	Turn Off an LED.																																							*
*	@WhiteLEDon()		-	Turn all LEDs On, creating white light.																												*
*	@WhiteLEDoff()	-	Turn all LEDs Off.																																						*
*	@blink()				-	Blink a given LED once.																																				*
*																																																									*
*	@UseButtons()		-	Initialize on-board buttons as Input (pulled up) pins.																				*
* @ReadButtons()	-	Read the state of on-board buttons. (This function is not working properly)										*
******************************************************************************************************************/
static void delay_for_blink(void);		// see definition below
void UseLEDs(void)
{
	GPIO_Init(LED_RED, Output, Digital, Two_mA, NoInterrupt);
	GPIO_Init(LED_BLUE, Output, Digital, Two_mA, NoInterrupt);
	GPIO_Init(LED_GREEN, Output, Digital, Two_mA, NoInterrupt);
}


void TurnOn(uint8_t pin)
{
	getPortAddr(pin,APB_BUS)->GPIO_DATA SET_BIT( getPinNumber(pin) );
}

void TurnOff(uint8_t pin)
{
	getPortAddr(pin,APB_BUS)->GPIO_DATA CLR_BIT( getPinNumber(pin) );
}


void WhiteLEDon(void)
{
	TurnOn(LED_RED);
	TurnOn(LED_BLUE);
	TurnOn(LED_GREEN);
	delay_for_blink();
}

void WhiteLEDoff(void)
{
	TurnOff(LED_RED);
	TurnOff(LED_BLUE);
	TurnOff(LED_GREEN);
}


/******************************************************************************************************************
* @delay_for_blink()																																															*
* @brief	-	Used to create delay between ON and OFF states of an LED.																							*
* @return	-	Nothing (void)																																												*
*																																																									*
* @Note		-	This function runs an empty loop for creating delay. It may be replaced by a timer api in future, if	*
*						blocking creates a problem.																																						*
*						This function is declared "static" so that it couldn't be used outside this file.											*
******************************************************************************************************************/
static void delay_for_blink(void)
{
	unsigned long i;
	for(i = 0; i<7500000; i++);
}

void blink(uint8_t pin)
{
	ToggleGPIOPin(pin);				delay_for_blink();
	ToggleGPIOPin(pin);				delay_for_blink();
}

void blinkWhiteLED(void)
{
	WriteToPin(LED_RED, PIN_SET);
	WriteToPin(LED_BLUE, PIN_SET);
	WriteToPin(LED_GREEN, PIN_SET);
	
	delay_for_blink();
	
	WriteToPin(LED_RED, PIN_RESET);
	WriteToPin(LED_BLUE, PIN_RESET);
	WriteToPin(LED_GREEN, PIN_RESET);
	
	delay_for_blink();
}


void UseButtons(void)
{
	DigitalPin(USER_SW1, InputPullUp);
	DigitalPin(USER_SW2, InputPullUp);
}

uint8_t ReadButtons(void)
{
	uint8_t sw1 = !ReadFromPin(USER_SW1);
	uint8_t sw2 = !ReadFromPin(USER_SW2);
	if(sw1)
	{
		if(sw2)
			return 0x3;
		else
			return 0x1;
	}else if(sw2)
			return 0x2;
	return 0;
}
