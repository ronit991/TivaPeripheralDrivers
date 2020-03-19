/******************************************************************************************************************
*	@file			-	TM4C123xxGPIO_DRIVER.c																																							*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains the definitions of GPIO Driver APIs.																													*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/



#include "TM4C123xxGPIO_DRIVER.h"



/******************************************************************************************************************
*																					User Switches and Onboard LEDs																					*
*	This information is valid for TM4C123GXL  board only.																														*
*		Pin:				PF0					PF1					PF2					PF3						PF4																							*
*		Function:		UserSw2			LedR				LedB				LedG					UserSw1																					*
******************************************************************************************************************/




/******************************************************************************************************************
*																						Functions for internal use																						*
*	Below are the definitions for functions which are meant to be used only by the GPIO Driver APIs.								*
*	Any use of these functions should be striclty avoided outside the scope of this driver as this may cause				*
*	serious problems within the microcontroller.																																		*
*	Uncomment the below defined functions when required.																														*
******************************************************************************************************************/

//static void GPIO_write_unlock(	GPIO_reg* pGPIO)
//{
//	pGPIO->GPIO_LOCK = 0x4C4F434B;
//	pGPIO->GPIO_CR |= 0x00000011;
//}

//static void GPIO_write_lock(	GPIO_reg* pGPIO)
//{
//	pGPIO->GPIO_LOCK = 0x00000000;
//	pGPIO->GPIO_CR &= 0x11111100;
//}



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*		Below are the prototypes for driver APIs																																			*
*		Definitions for these can be found in TM4C123xxGPIO_DRIVER.c file																							*
*																																																									*
*	1. 	GPIO_ClockControl()		-		Enable/Disable clock for a GPIO port.																							*
*	2. 	GPIO_Init()						-		Initialize a GPIO pin. Use this function in your programs only if you	need a fine *
*																control over the drive strength of the pin.																				*
*																Otherwise use functions 4/5/6 for simplicity.																			*
*	3. 	GPIO_DeInit()					-		Reset and turn off a GPIO port.																										*
*	4. 	DigitalPin()					-		Initialize a GPIO pin in Digital mode with 8mA drive strength.										*
*	5. 	AnalogPin()						-		Initialize a GPIO pin in Analog	mode with 8mA drive strength.											*
*	6. 	InterruptPin()				-		Initialize a GPIO pin in Digital(input) mode with interrupt reception.						*
*	7. 	WriteToPin()					-		Write digital values to a GPIO pin																								*
*	8. 	WriteToPort()					-		Write digital values to a GPIO port																								*
*	9. 	ToggleGPIOPin()				-		Toggle the state of a GPIO pin																										*
*	10. ReadFromPin()					-		Read data from a GPIO pin																													*
*	11. ReadFromPort()				-		Read data from a GPIO port																												*
******************************************************************************************************************/



/******************************************************************************************************************
*	@GPIO_ClockControl																																															*
* @brief			-	This function is used to enable or disable clock for a particular GPIO port												*
*	@GPIOPort		- Name of the GPIO port for which clock needs to be enabled or disabled.														*
*	@ClkEn			- This variable speifies whether we have to enable or disable the clock.														*
*								Use (I) ENABLE or (II) DISABLE macros for this variable for better readability.										*
*								These macros are defined in TM4C123xx.h header file under the section "Miscellaneous macros and		*
*								shorthands".																																											*
* @return			-	Nothing (void).																																										*
*																																																									*
*	@Note				-	Refer to section Pg 340 of datasheet for detailed information.																		*
******************************************************************************************************************/
void	GPIO_ClockControl(uint8_t GPIOPort, uint8_t ClkEn)
{
	if(ClkEn == ENABLE)
	{
		switch(GPIOPort)												// Enable the clock for the port.
		{
			case GPIO_PORT_A:		GPIOA_PCLK_EN();				break;	// These macros are defined in TM4C123xx.h file in section 2.2
			case GPIO_PORT_B:		GPIOB_PCLK_EN(); 				break;
			case GPIO_PORT_C:		GPIOC_PCLK_EN(); 				break;
			case GPIO_PORT_D:		GPIOD_PCLK_EN(); 				break;
			case GPIO_PORT_E:		GPIOE_PCLK_EN(); 				break;
			case GPIO_PORT_F:		GPIOF_PCLK_EN(); 				break;
		}
	}
	else if(ClkEn == DISABLE)
	{
		switch(GPIOPort)												// Disable the clock.
		{
			case GPIO_PORT_A:		GPIOA_PCLK_DIS(); 			break;	// These macros are defined in TM4C123xx.h file in section 2.2
			case GPIO_PORT_B:		GPIOB_PCLK_DIS(); 			break;
			case GPIO_PORT_C:		GPIOC_PCLK_DIS(); 			break;
			case GPIO_PORT_D:		GPIOD_PCLK_DIS(); 			break;
			case GPIO_PORT_E:		GPIOE_PCLK_DIS(); 			break;
			case GPIO_PORT_F:		GPIOF_PCLK_DIS(); 			break;
		}
	}
}
	
	

/******************************************************************************************************************
*	@GPIO_Init																																																			*
*	@brief					- This function is used to Initialize/Configure a GPIO Pin.																			*
*	@pin						-	Pin Number.																																										*
*	@ioMode					-	Direction (In/Out), and Pin Type (Pull Up, Pull Down, Open Drain).														*
*	@AltFn					-	Alternate Function Number.																																		*
*	@pinMode				-	Pin Mode ( Analog / Digital ).																																*
*	@DriveStrength	- Drive Strength ( 2mA, 4mA, 8mA ).																															*
* @Trigger				-	Interrupt Trigger Mode ( Rising/Falling/Both Edge trigger or High/Low Level trigger ).				*
* @return					-	Nothing (void).																																								*
*																																																									*
*	@Note						-	Steps to configure a GPIO pin:																																*
*										1. Provide clock to the GPIO port.																														*
*										2. Set the direction for the GPIO pin.																												*
*										3. Configure Alternate function.																															*
*										4. Configure Drive strength.																																	*
*										5. Configure output type of the pin ( Pull Up/Down or Open Drain).														*
*												5.1 (Optional) Configure slew rate for the pin.																						*
*										6. Configure pin mode (Analog / Digital).																											*
*										7. Configure type, event, and mask for interrupt.																							*
* 									Refer to section 10.3(Pg 656) of datasheet for detailed information on all these steps.				*
******************************************************************************************************************/
void	GPIO_Init(uint8_t pin, uint8_t ioMode, uint8_t pinMode, uint8_t DriveStrength, uint8_t Trigger)
{
	GPIO_reg* pGPIO =		getPortAddr(pin,APB_BUS);		//	Pointer to the GPIO port.
	uint8_t GPIO_Port = getPortName(pin);						//	Name of the GPIO port.
	uint8_t PinNumber = getPinNumber(pin);					//	Pin number which needs to be initialized.
	
	//	Step1:	Enable Clock.
	GPIO_ClockControl(GPIO_Port, ENABLE);
	
	//	Step2,5:	Set pin direction, and mode by setting/clearing appropriate bits in the GPIODIR and GPIO(PUR/PDR/ODR) registers.
	switch(ioMode)
	{
		case OutputOpenDrain:			pGPIO->GPIO_ODR	SET_BIT( PinNumber );
															pGPIO->GPIO_DIR SET_BIT( PinNumber );
															break;
		case Output:							pGPIO->GPIO_ODR	CLR_BIT( PinNumber );
															pGPIO->GPIO_DIR SET_BIT( PinNumber );
															break; 
		case InputPullUp:					pGPIO->GPIO_PUR	SET_BIT( PinNumber );
															pGPIO->GPIO_DIR CLR_BIT(PinNumber);
															break;
		case InputPullDown:				pGPIO->GPIO_PDR	SET_BIT( PinNumber );
															pGPIO->GPIO_DIR CLR_BIT(PinNumber);
															break;
		case Input:								pGPIO->GPIO_PUR	CLR_BIT( PinNumber );
															pGPIO->GPIO_PDR	CLR_BIT( PinNumber );
															pGPIO->GPIO_DIR CLR_BIT(PinNumber);
															break;
	}
	
	
	/****************************************************************************************************************
	*	Step3:	Configure Alternate function.																																					*
	*	Alternate function is not configured here as it is done by the Driver APIs of the respective peripherals.			*
	****************************************************************************************************************/
	
	
	/****************************************************************************************************************
	*	Step 4:	Configure drive strength.																																							*
	*					Set the drive strength for each of the pins by setting the appropriate bits in the GPIODR2R, GPIODR4R	*
	*					and GPIODR8R registers.																																								*
	****************************************************************************************************************/
	switch(DriveStrength)
	{
		case Two_mA		:		pGPIO->GPIO_DR2R SET_BIT( PinNumber );		break;
		case Four_mA	:		pGPIO->GPIO_DR4R SET_BIT( PinNumber );		break;
		case Eight_mA	:		pGPIO->GPIO_DR8R SET_BIT( PinNumber );		break;
	}

	
	/****************************************************************************************************************
	*	Step 6:	Configure Pin Mode (Analog/Digital)																																		*
	*					Set the appropriate bit in GPIO(DEN/AMSEL) registers to enable digital/analog function for the pin.		*
	****************************************************************************************************************/
	switch(pinMode)
	{
		case Digital:			pGPIO->GPIO_DEN		SET_BIT( PinNumber );		break;
		case Analog	:			pGPIO->GPIO_AMSEL	SET_BIT( PinNumber );		break;
	}
	
	/****************************************************************************************************************
	*	Step7:	Configure Type, Event, and Mask for Interrupts																												*
	*																																																								*
	*	To prevent false interrupts, following steps should be taken when re-configuring GPIO Edge and Interrupt			*
	*	 sense registers:-																																														*
	*		1	Mask the corresponding port by clearing the IME field in the GPIOIM register.															*
	*				1.1	Masking the interrupt disallows the interrupt to be sent to the interrupt controller.								*
	*						Mask => Set the bit.	Unmask => Clear the bit.																											*
	*		2 Configure the IS and IBE field in the GPIOIS and GPIOIBE registers.																				*
	*				2.1	Interrupt Sense (IS)																																								*
	*						Level detection if the bit is Set.																																	*
	*						Edge	detection if the bit is Cleared.																															*
	*				2.2 Interrupt Both Edges (IBE)																																					*
	*						If bit is Set			:	Interrupt is detected on both rising and falling edges.													*
	*						If bit is Cleared	:	Interrupt is controlled by GPIOIEV register.																		*
	*						__this however, works only if IS register is configured to detect edges__														*
	*		3	Configure Interrupt Event Register in case of single-edge or level triggered interrupt.										*
	*				Bit = 1		:	Rising  Edge / High Level																																		*
	*				Bit = 0		: Falling Edge / Low  Level																																		*
	*		4	Clear the GPIORIS register.																																								*
	*				4.1	GPIORIS is a Read-Only type register.																																*
	*						If a bit is Set		:	It suggests that an Interrupt has occurred on the corresponding pin.						*
	*						If a bit is Reset	:	It suggests that no interrupt has occurred on the corresponding pin.						*
	*				4.2	Clearing the Register																																								*
	*						For a level detected interrupt, the corresponding bit in this register is automatically cleared			*
	*						when the interrupt has been serviced.																																*
	*						For a edge detected interrupt, the bit is cleared by writing a '1' in the corresponding bit in			*
	*						the GPIOICR register. Writing a '0' to any of the bits has no effect. Also, level triggered					*
	*						interrupts are not affected by writing '1' to this register.																				*
	*		5	Unmask the port by setting the IME field in the GPIOIM register.																					*
	****************************************************************************************************************/
	if(Trigger == NoInterrupt)
	{ // do nothing
	}
	else
	{
		uint8_t clearICR = 0;											// Flag to clear ICR register for Edge-triggered interrupts.
		pGPIO->GPIO_IM CLR_BIT( PinNumber );			// Mask the interrupt so that it doesn't cause any unwanted event while configuring the interrupt registers.
		switch(Trigger)
		{
			case RisingEdge:	pGPIO->GPIO_IS		CLR_BIT( PinNumber );
												pGPIO->GPIO_IBE 	CLR_BIT( PinNumber );
												pGPIO->GPIO_IEV 	SET_BIT( PinNumber );
												clearICR = 1;
												break;
			
			case FallingEdge:	pGPIO->GPIO_IS		CLR_BIT( PinNumber );
												pGPIO->GPIO_IBE 	CLR_BIT( PinNumber );
												pGPIO->GPIO_IEV 	CLR_BIT( PinNumber );
												clearICR = 1;
												break;
			
			case BothEdges:		pGPIO->GPIO_IS		CLR_BIT( PinNumber );
												pGPIO->GPIO_IBE 	SET_BIT( PinNumber );
												clearICR = 1;
												break;
												
			case HighLevel:		pGPIO->GPIO_IS		SET_BIT( PinNumber );
												pGPIO->GPIO_IBE		CLR_BIT( PinNumber );
												pGPIO->GPIO_IEV		SET_BIT( PinNumber );
												break;
			
			case LowLevel:		pGPIO->GPIO_IS		SET_BIT( PinNumber );
												pGPIO->GPIO_IBE 	CLR_BIT( PinNumber );
												pGPIO->GPIO_IEV 	CLR_BIT( PinNumber );
												break;
		}
		if(clearICR)
			pGPIO->GPIO_ICR SET_BIT( PinNumber );		//	Clear ICR register for Edge-triggered interrupts.
		
		pGPIO->GPIO_IM SET_BIT( PinNumber );			//	Disable the interrupt mask to re-enable the interrupts.
	}
}



/******************************************************************************************************************
*	@GPIO_DeInit()																																																	*
*	@brief				-	This function DeInitializes or Resets a GPIO port																								*
* @GPIO_PORT		-	This is the name of the GPIO Port which needs to be reset.																			*
* @return				-	Nothing (void).																																									*
*																																																									*
*	@Note					- To reset a GPIO port, the corresponding bit in the SRGPIO register needs to be set. Clock to		*
*									the port is then disabled to save power, and prevent access to the port.												*
******************************************************************************************************************/
void	GPIO_DeInit(uint8_t GPIOPort)
{
	SYSCTL->SRGPIO	SET_BIT( GPIOPort );				// Reset the port by setting the appropriate bit in SRGPIO register.
	SYSCTL->SRGPIO	CLR_BIT( GPIOPort );				// The bit is cleared so that it doesn't always remain in reset state.
	
	GPIO_ClockControl(GPIOPort,DISABLE);				// Disable the clock.
}
	
	

/******************************************************************************************************************
*	@ReadFromPin()																																																	*
*	@brief				-	This function reads data from a GPIO pin																												*
* @pin					-	This is the pin from which we have to read the data																							*
* @return				-	Digital value on the specified pin.																															*
******************************************************************************************************************/
uint8_t	ReadFromPin(uint8_t pin)
{
	GPIO_reg* pGPIOx = getPortAddr(pin, APB_BUS);
	return GET_BIT( pGPIOx->GPIO_DATA, getPinNumber(pin) );
//	The above statement is equivalent to return ( pGPIO->GPIO_DATA & (1<<PinNumber) )
}
	

	
/******************************************************************************************************************
*	@ReadFromPort()																																																	*
*	@brief				-	This function reads data from a GPIO port																												*
* @GPIOPort			-	This is the GPIO Port from which we have to read the data.																			*
* @return				-	Digital values on all of the pins of the specified port.																				*
******************************************************************************************************************/
uint8_t	ReadFromPort(uint8_t GPIOPort)
{
	GPIO_reg* pGPIO = getPortAddr(GPIOPort, APB_BUS);
	return (uint8_t)( pGPIO->GPIO_DATA );
}
	
	

/******************************************************************************************************************
*	@WriteToPin()																																																		*
*	@brief				-	This function writes the given value to a GPIO pin																							*
* @pin					-	This is the pin to which we have to write the data																							*
*	@Value				-	Value which is to be written to the pin.																												*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void WriteToPin(uint8_t pin, uint8_t Value)
{
	GPIO_reg* pGPIO = getPortAddr(pin, APB_BUS);
	if(Value == PIN_SET)					pGPIO->GPIO_DATA SET_BIT( getPinNumber(pin) );
	else if(Value == PIN_RESET)		pGPIO->GPIO_DATA CLR_BIT( getPinNumber(pin) );
	
	//	The above statement is equivalent to the following:-
	//	if(Value == PIN_SET)					pGPIO->GPIO_DATA |=	(1<<PinNumber);
	//	else if(Value == PIN_RESET)		pGPIO->GPIO_DATA &= ~(1<<PinNumber);
}
	


/******************************************************************************************************************
*	@WriteToPort()																																																	*
*	@brief				-	This function writes the given data to a GPIO port																							*
* @GPIO_PORT		-	This is the GPIO Port to which we have to write the data.																				*
*	@Values				-	Values which is to be written to the port.																											*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void WriteToPort(uint8_t GPIO_PORT, uint8_t Values)
{
	GPIO_reg* pGPIO = getPortAddr(GPIO_PORT, APB_BUS);
	pGPIO->GPIO_DATA = Values;
}
	
	

/******************************************************************************************************************
*	@ToggleGPIOPin()																																																*
*	@brief				-	This function toggles the state of a GPIO pin																										*
* @pin					-	This is the pin which needs to be toggled.																											*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void ToggleGPIOPin(uint8_t pin)
{
	getPortAddr(pin,APB_BUS)->GPIO_DATA ^= (1<<getPinNumber(pin));
	//	The above statement is equivalent to pGPIOx->GPIO_DATA ^= (1<<PinNumber)
	//	Remember x^1 = x'
}



/******************************************************************************************************************
*	@DigitalPin()																																																		*
*	@brief				-	This function configures a GPIO pin in Digital mode																							*
* @pin					-	This variable holds the pin number which needs to be configured.																*
*	@IOmode				-	Input/Output mode.																																							*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void DigitalPin(uint8_t pin, uint8_t IOmode)
{
	GPIO_Init(pin, IOmode, Digital, Two_mA, NoInterrupt);
}



/******************************************************************************************************************
*	@AnalogPin()																																																		*
*	@brief				-	This function configures a GPIO pin in Analog mode																							*
* @pin					-	This variable holds the pin number which needs to be configured.																*
*	@IOmode				-	Input/Output mode.																																							*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void	AnalogPin(uint8_t pin, uint8_t IOmode)
{
	GPIO_Init(pin, IOmode, Analog, Two_mA, NoInterrupt);
}



/******************************************************************************************************************
*	@InterruptPin()																																																	*
*	@brief				-	This function configures a GPIO pin as an Interrupt pin																					*
* @pin					-	This variable holds the pin number which needs to be configured.																*
*	@triggerMode	-	Interrupt Trigger Mode ( Rising/Falling/Both Edge trigger or High/Low Level trigger )						*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void	InterruptPin(uint8_t pin, uint8_t triggerMode)
{
	uint8_t PortName = getPortName(pin);
	uint8_t PinNumber = getPinNumber(pin);
	
	// Initialize the given pin with the specified interrupt trigger mode.
	GPIO_Init(pin, Input, Digital, Eight_mA, triggerMode);
	
	/****************************************************************************************************************
	*	Enable interrupt reception on the corresponding GPIO port by setting the appropriate bit in the NVIC Enable		*
	*	register (in our case, EN0).																																									*
	****************************************************************************************************************/
	switch(PortName)
	{
		case GPIO_PORT_A:				NVIC->EN[0] SET_BIT( NVIC_EN0_GPIOA );			break;
		case GPIO_PORT_B:				NVIC->EN[0] SET_BIT( NVIC_EN0_GPIOB );			break;
		case GPIO_PORT_C:				NVIC->EN[0] SET_BIT( NVIC_EN0_GPIOC );			break;
		case GPIO_PORT_D:				NVIC->EN[0] SET_BIT( NVIC_EN0_GPIOD );			break;
		case GPIO_PORT_E:				NVIC->EN[0] SET_BIT( NVIC_EN0_GPIOE );			break;
		case GPIO_PORT_F:				NVIC->EN[0] SET_BIT( NVIC_EN0_GPIOF );			break;
	}
}



/******************************************************************************************************************
*																									Broken APIs																											*
*		Below are the definitions for functions/APIs which are not in a working state yet.														*
******************************************************************************************************************/
void	interruptpin(uint8_t pin, void (*isr_func)(void), uint8_t triggerMode)
{
	uint8_t PortName = getPortName(pin);
	uint8_t PinNumber = getPinNumber(pin);

	GPIO_Init(pin, Input, Digital, Eight_mA, triggerMode);
	
	/****************************************************************************************************************
	*	Specify the address of the ISR, and Enable the interrupt by setting the appropriate bit in the NVIC Enable		*
	*	register (in our case, EN0).																																									*
	****************************************************************************************************************/
	switch(PortName)
	{
		case GPIO_PORT_A:	ExceptionHandlers->_GPIOA = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<0;
											break;
		case GPIO_PORT_B:	ExceptionHandlers->_GPIOB = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<1;
											break;
		case GPIO_PORT_C:	ExceptionHandlers->_GPIOC = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<2;
											break;
		case GPIO_PORT_D:	ExceptionHandlers->_GPIOD = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<3;
											break;
		case GPIO_PORT_E:	ExceptionHandlers->_GPIOE = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<4;
											break;
		case GPIO_PORT_F: ExceptionHandlers->_GPIOF = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<30;
											break;
	}
}


