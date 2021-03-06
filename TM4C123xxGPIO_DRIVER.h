/******************************************************************************************************************
*	@file			-	TM4C123xxGPIO_DRIVER.h																																							*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains prototypes of GPIO Driver APIs. Bit position macros and shorthands which are used by the			*
*	GPIO Driver APIs are also defined here.																																					*
*																																																									*
*	Things that need to be changed/improved:-																																				*
*	<>	Remove Alternate function configuration from GPIO_Init() function. Alternate functionality is configured		*
*			by their respective driver api(s).																																					*
*	<>	Remove getAltFnNum() function.																																							*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/



#ifndef TM4C123XXGPIO_DRIVER_H
#define TM4C123XXGPIO_DRIVER_H

#include "TM4C123xx.h"



/******************************************************************************************************************
*																								Bit Position Macros																								*
******************************************************************************************************************/
// NVIC EN0 Register
#define NVIC_EN0_GPIOA			0
#define NVIC_EN0_GPIOB			1
#define NVIC_EN0_GPIOC			2
#define NVIC_EN0_GPIOD			3
#define NVIC_EN0_GPIOE			4
#define NVIC_EN0_GPIOF			30



/******************************************************************************************************************
*																			Miscellaneous macros and aliases																					*
******************************************************************************************************************/
//	GPIO Pin Modes
#define Digital						0
#define Analog						1

//	GPIO Pin Drive Strength
#define Two_mA						0
#define Four_mA						1
#define Eight_mA					2

//	GPIO Pull-Up, Pull-Down, and Open Drain configuration
#define Input							0
#define InputPullUp				1
#define InputPullDown			2
#define Output						3
#define OutputOpenDrain		4

#define PullUp						0
#define PullDn						1
#define OpenDr						2

//	GPIO Interrupt Trigger Modes
#define NoInterrupt				0
#define RisingEdge				1
#define FallingEdge				2
#define BothEdges					3
#define	HighLevel					4
#define	LowLevel					5



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*		Below are the prototypes for driver APIs																																			*
*		Definitions for these can be found in TM4C123xxGPIO_DRIVER.c file																							*
*																																																									*
*	1. 	GPIO_ClockControl()		-		Enable/Disable clock for a GPIO port.																							*
*	2. 	GPIO_Init()						-		Initialize a GPIO pin. Use this function in your programs only if you	need a fine	*
*																control over the drive strength of the pin.																				*
*																Otherwise use functions 4/5/6 for simplicity.																			*
*	3. 	GPIO_DeInit()					-		Reset and turn off a GPIO port.																										*
*	4. 	DigitalPin()					-		Initialize a GPIO pin in Digital mode with 2mA drive strength.										*
*	5. 	AnalogPin()						-		Initialize a GPIO pin in Analog	 mode with 2mA drive strength.										*
*	6. 	InterruptPin()				-		Initialize a GPIO pin in Digital(input) mode with interrupt reception.						*
*	7. 	WriteToPin()					-		Write digital values to a GPIO pin																								*
*	8. 	WriteToPort()					-		Write digital values to a GPIO port																								*
*	9. 	ToggleGPIOPin()				-		Toggle the state of a GPIO pin																										*
*	10. ReadFromPin()					-		Read data from a GPIO pin																													*
*	11. ReadFromPort()				-		Read data from a GPIO port																												*
******************************************************************************************************************/
void	GPIO_ClockControl( uint8_t GPIO_Port, uint8_t Clk_En);
void	GPIO_Init(	 uint8_t pin, uint8_t ioMode, uint8_t pinMode, uint8_t DriveStrength, uint8_t Trigger);
void	GPIO_DeInit( uint8_t GPIO_PORT);

void	DigitalPin(  uint8_t pin, uint8_t IOmode);
void	AnalogPin(	 uint8_t pin, uint8_t IOmode);
void	InterruptPin(uint8_t pin, uint8_t triggerMode);

void	WriteToPin( uint8_t pin, uint8_t Value);
void	WriteToPort(uint8_t GPIO_PORT, uint8_t Values);

void	ToggleGPIOPin(uint8_t pin);

uint8_t	ReadFromPin(uint8_t pin);
uint8_t	ReadFromPort(uint8_t GPIO_PORT);


/******************************************************************************************************************
*																									Broken APIs																											*
*		Below are the prototypes for functions/APIs which are not in a working state yet.															*
******************************************************************************************************************/
void	interruptpin(uint8_t pin, void (*isr_func)(void), uint8_t triggerMode);

#endif
