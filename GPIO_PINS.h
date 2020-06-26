/******************************************************************************************************************
*	@file			-	GPIO_PINS.h																																													*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
* This file contains names for GPIO pins. These can be used instead of using port address and pin number. Port		*
*	address and pin number can be extracted from pin name using functions defined in this file.											*
* @Note			-	Parts of this code(Section 0) are generic, and these can be applied to any microcontroller.					*
*							However, codes present in Section 1 & 2 might not work on other microcontrollers. Further, code in	*
*							Section 3 works only on TM4C123GXL board.	For function definitions, see GPIO_PINS.c file.						*
*																																																									*
*							ReadButtons() function is not working properly (see section 3). This needs a diagnosis.							*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/

/******************************************************************************************************************
*	Sections in this file:-																																													*
* 0. GPIO Pin Aliases.																																														*
* 1. User LEDs & Buttons. (for TM4C123GH6PM)																																			*
* 2. Pin number & Address resolver functions.																																			*
* 3. Functions for on-board LEDs and Buttons. (for TM4C123GH6PM)																									*
******************************************************************************************************************/

#ifndef GPIO_PINS_H
#define GPIO_PINS_H

#include "TM4C123xx.h"


// Section 0: GPIO Pin Aliases
#define PA0 10
#define PA1 11
#define PA2 12
#define PA3 13
#define PA4 14
#define PA5 15
#define PA6 16
#define PA7 17

#define PB0 20
#define PB1 21
#define PB2 22
#define PB3 23
#define PB4 24
#define PB5 25
#define PB6 26
#define PB7 27

#define PC0 30
#define PC1 31
#define PC2 32
#define PC3 33
#define PC4 34
#define PC5 35
#define PC6 36
#define PC7 37

#define PD0 40
#define PD1 41
#define PD2 42
#define PD3 43
#define PD4 44
#define PD5 45
#define PD6 46
#define PD7 47

#define PE0 50
#define PE1 51
#define PE2 52
#define PE3 53
#define PE4 54
#define PE5 55
#define PE6 56
#define PE7 57

#define PF0 60
#define PF1 61
#define PF2 62
#define PF3 63
#define PF4 64
#define PF5 65
#define PF6 66
#define PF7 67


// Section 1: User LEDs & Buttons
#define LED_RED			PF1
#define LED_BLUE		PF2
#define LED_GREEN		PF3

#define USER_SW1		PF4
#define USER_SW2		PF0



/******************************************************************************************************************
*	Section 2: Pin number & Address resolver functions																															*
*																																																									*
*	@getPortAddr()		-	Get pointer to a GPIO port using name of a pin or port.																			*
* @getPortName()		-	Get port name for a given pin.																															*
*	@getPinNumber()		-	Get pin number(i.e. 3 for PF3, 7 for PA7 etc.) of a pin.																		*
******************************************************************************************************************/
//GPIO_reg* getPortAddrFromPortName(uint8_t GPIO_PORT, uint8_t bus);
GPIO_reg* getPortAddr(uint8_t pin, uint8_t bus);
uint8_t getPortName(uint8_t pin);
uint8_t getPinNumber(uint8_t pin);


/******************************************************************************************************************
* Section 3: Functions for on-board LEDs and Buttons																															*
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
void UseLEDs(void);
void TurnOn(uint8_t pin);
void TurnOff(uint8_t pin);
void blink(uint8_t pin);
void blinkWhiteLED(void);
void WhiteLEDon(void);
void WhiteLEDoff(void);

void UseButtons(void);
uint8_t ReadButtons(void);

#endif
