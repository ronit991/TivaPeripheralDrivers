/******************************************************************************************************************
*	@file			-	TM4C123xxGPIO_DRIVER.c																																							*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains the definitions of GPIO Driver APIs.																													*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
******************************************************************************************************************/



#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"



/******************************************************************************************************************
*																					GPIO Interrupt Pin Numbers																							*
*	These variables hold the pin number which has been configured as an Interrupt pin for a particular port.				*
*	Default value for all these variables is 99. This value also suggests that a particular port does not have any 	*
*	pin configured as an interrupt pin. While de-initializing a GPIO port or while removing the interrupt, the			*
*	corresponding variable is re-assigned the value 99.																															*
******************************************************************************************************************/
uint8_t GPIOA_INT_PIN = 99;
uint8_t GPIOB_INT_PIN = 99;
uint8_t GPIOC_INT_PIN = 99;
uint8_t GPIOD_INT_PIN = 99;
uint8_t GPIOE_INT_PIN = 99;
uint8_t GPIOF_INT_PIN = 99;



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
******************************************************************************************************************/

static void GPIO_write_unlock(	GPIO_reg* pGPIO)
{
	pGPIO->GPIO_LOCK = 0x4C4F434B;
	pGPIO->GPIO_CR |= 0x00000011;
}

static void GPIO_write_lock(	GPIO_reg* pGPIO)
{
	pGPIO->GPIO_LOCK = 0x00000000;
	pGPIO->GPIO_CR &= 0x11111100;
}



/******************************************************************************************************************
*																				User APIs Supported by this Driver																				*
*																																																									*
*	void			GPIO_ClockControl()		-- Enable/Disable clock for a GPIO port																					*
*	void			GPIO_Init()						-- Initialize a GPIO port																												*
*	void			GPIO_DeInit()					-- De-Initialize or Reset a GPIO port																						*
*	void			WriteToPin()					-- Write data to a GPIO pin																											*
*	void			WriteToPort()					-- Write data to a GPIO port																										*
*	void			ToggleGPIOPin()				-- Toggle the state of a GPIO pin																								*
*	uint8_t		ReadFromPin()					-- Read data from a GPIO pin																										*
*	uint8_t		ReadFromPort()				-- Read data from a GPIO port																										*
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
			case GPIO_PORT_A:	GPIOA_PCLK_EN(); break;
			case GPIO_PORT_B:	GPIOB_PCLK_EN(); break;
			case GPIO_PORT_C:	GPIOC_PCLK_EN(); break;
			case GPIO_PORT_D:	GPIOD_PCLK_EN(); break;
			case GPIO_PORT_E:	GPIOE_PCLK_EN(); break;
			case GPIO_PORT_F:	GPIOF_PCLK_EN(); break;
		}
	}
	else if(ClkEn == DISABLE)
	{
		switch(GPIOPort)												// Disable the clock and set interrupt pin number to default.
		{
			case GPIO_PORT_A:		GPIOA_PCLK_DIS(); 	GPIOA_INT_PIN = 99;		break;
			case GPIO_PORT_B:		GPIOB_PCLK_DIS(); 	GPIOB_INT_PIN = 99;		break;
			case GPIO_PORT_C:		GPIOC_PCLK_DIS(); 	GPIOC_INT_PIN = 99;		break;
			case GPIO_PORT_D:		GPIOD_PCLK_DIS(); 	GPIOD_INT_PIN = 99;		break;
			case GPIO_PORT_E:		GPIOE_PCLK_DIS(); 	GPIOE_INT_PIN = 99;		break;
			case GPIO_PORT_F:		GPIOF_PCLK_DIS(); 	GPIOF_INT_PIN = 99;		break;
		}
	}
}
	
	

/******************************************************************************************************************
*	@GPIO_Init																																																			*
*	@brief					- This function is used to Initialize/Configure a GPIO Pin.																			*
*	@pin						-	Pin Number.																																										*
*	@Dir						-	Direction (In/Out).																																						*
*	@AltFn					-	Alternate Function Number.																																		*
*	@OpType					-	Output Mode Type ( Pull Up, Pull Down, Open Drain ).																					*
*	@Mode						-	Pin Mode ( Analog / Digital ).																																*
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
void	GPIO_Init(uint8_t pin, uint8_t Dir, uint8_t AltFn, uint8_t OpType, uint8_t Mode, uint8_t DriveStrength, uint8_t Trigger)
{
	GPIO_reg* pGPIO =		getPortAddr(pin,APB_BUS);		//	Variable which points to the GPIO port.
	uint8_t GPIO_Port = getPortName(pin);						//	Variable which stores the name of the GPIO port.
	uint8_t PinNumber = getPinNumber(pin);					//	Variable which stores the Pin number which needs to be initialized.
	
	//	Step1:	Enable Clock.
	GPIO_ClockControl(GPIO_Port, ENABLE);
	
	//	Step2:	Set pin direction by setting or clearing appropriate bits in the GPIODIR register.
	switch(Dir)
	{
		case OUT:		pGPIO->GPIO_DIR |= 1<<(PinNumber);						break;
		case IN:		pGPIO->GPIO_DIR &= ~( 1<<(PinNumber) );				break;
	}
	
	//	Step3:	Configure Alternate function.
	if(AltFn != NoAlternateFunction)
	{
		pGPIO->GPIO_AFSEL	|=	1<<(PinNumber);												// Use the pin in alternate function mode.
		
		/**************************************************************************************************************
		*	Get the alternate function number/index  using getAltFnNum() function so that the corresponding bits could	*
		*	be writtten to the GPIOPCTL register. For more information on this step, see section 10.3 in the datasheet.	*
		*	Also see table 23-5 (Page 1351) to check for the peripheral which needs to be used in place of the GPIO.		*
		**************************************************************************************************************/
		uint8_t AF = getAltFnNum(AltFn);
		pGPIO->GPIO_PCTL	&= ~(0xF<<(PinNumber*4));									// Clear the appropriate bits in the PCTL register.
		//	Replace the cleared bits with appropriate function selection bits in the GPIOPCTL register.
		switch(AF)
		{
			case 1: 	pGPIO->GPIO_PCTL	|= ( 0x1 <<(PinNumber*4) );				break;
			case 2: 	pGPIO->GPIO_PCTL	|= ( 0x2 <<(PinNumber*4) );				break;
			case 3: 	pGPIO->GPIO_PCTL	|= ( 0x3 <<(PinNumber*4) );				break;
			case 4: 	pGPIO->GPIO_PCTL	|= ( 0x4 <<(PinNumber*4) );				break;
			case 5: 	pGPIO->GPIO_PCTL	|= ( 0x5 <<(PinNumber*4) );				break;
			case 6: 	pGPIO->GPIO_PCTL	|= ( 0x6 <<(PinNumber*4) );				break;
			case 7: 	pGPIO->GPIO_PCTL	|= ( 0x7 <<(PinNumber*4) );				break;
			case 8: 	pGPIO->GPIO_PCTL	|= ( 0x8 <<(PinNumber*4) );				break;
			case 9: 	pGPIO->GPIO_PCTL	|= ( 0x9 <<(PinNumber*4) );				break;
			case 15:	pGPIO->GPIO_PCTL	|= ( 0xA <<(PinNumber*4) );	 			break;
			default:	break;
		}
	}
	
	/****************************************************************************************************************
	*	Step 4:	Configure drive strength.																																							*
	*					Set the drive strength for each of the pins by setting the appropriate bits in the GPIODR2R, GPIODR4R	*
	*					and GPIODR8R registers.																																								*
	****************************************************************************************************************/
	switch(DriveStrength)
	{
		case Two_mA		:		pGPIO->GPIO_DR2R |= 1<<( PinNumber );			break;
		case Four_mA	:		pGPIO->GPIO_DR4R |= 1<<( PinNumber );			break;
		case Eight_mA	:		pGPIO->GPIO_DR8R |= 1<<( PinNumber );			break;
	}
	
	/****************************************************************************************************************
	*	Step 5:	Configure Pull Up/Down | Open Drain mode																															*
	*					Set the pins to have Pull Up/Down or Open Drain functionality by setting the appropriate bits in the	*
	*					GPIO(PUR/PDR/ODR) registers.																																					*
	****************************************************************************************************************/
	switch(OpType)
	{
		case PullUp	:			pGPIO->GPIO_PUR	|= 1<<( PinNumber );			break;
		case PullDn	:			pGPIO->GPIO_PDR	|= 1<<( PinNumber );			break;
		case OpenDr	:			pGPIO->GPIO_ODR	|= 1<<( PinNumber );			break;
	}
	
	/****************************************************************************************************************
	*	Step 6:	Configure Pin Mode (Analog/Digital)																																		*
	*					Set the appropriate bit in GPIO(DEN/AMSEL) registers to enable digital/analog function for the pin.		*
	****************************************************************************************************************/
	switch(Mode)
	{
		case Digital:			pGPIO->GPIO_DEN		|= 1<<( PinNumber );	break;
		case Analog	:			pGPIO->GPIO_AMSEL	|= 1<<( PinNumber );	break;
	}
	
	/****************************************************************************************************************
	*	Step7:	Configure Type, Event, and Mask for Interrupts																												*
	*																																																								*
	*	To prevent false interrupts, following steps should be taken when re-configuring GPIO Edge and Interrupt			*
	*	 sense registers:-																																														*
	*		1	Mask the corresponding port by clearing the IME field in the GPIOIM register.															*
	*				1.1	Masking the interrupt allows the interrupt to be sent to the interrupt controller.									*
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
	*				Bit = Set		:	Rising  Edge / High Level																																	*
	*				Bit = Clear	: Falling Edge / Low  Level																																	*
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
		uint8_t clearICR = 0;
		pGPIO->GPIO_IM &= ~( 1<<PinNumber );
		switch(Trigger)
		{
			case RisingEdge:	pGPIO->GPIO_IS	&= ~(	1<<PinNumber );
												pGPIO->GPIO_IBE &= ~(	1<<PinNumber );
												pGPIO->GPIO_IEV |=	(	1<<PinNumber );
												clearICR = 1;
												break;
			
			case FallingEdge:	pGPIO->GPIO_IS	&= ~( 1<<PinNumber );
												pGPIO->GPIO_IBE &= ~( 1<<PinNumber );
												pGPIO->GPIO_IEV &= ~( 1<<PinNumber );
												clearICR = 1;
												break;
			
			case BothEdges:		pGPIO->GPIO_IS	&= ~( 1<<PinNumber );
												pGPIO->GPIO_IBE |=	( 1<<PinNumber );
												clearICR = 1;
												break;
												
			case HighLevel:		pGPIO->GPIO_IS	|=	( 1<<PinNumber );
												pGPIO->GPIO_IBE	&= ~( 1<<PinNumber );
												pGPIO->GPIO_IEV	|=	( 1<<PinNumber );
												break;
			
			case LowLevel:		pGPIO->GPIO_IS	|=	( 1<<PinNumber );
												pGPIO->GPIO_IBE &= ~( 1<<PinNumber );
												pGPIO->GPIO_IEV &= ~( 1<<PinNumber );
												break;
		}
		if(clearICR)
			pGPIO->GPIO_ICR |= ( 1<<PinNumber );		//	Clear ICR register for Edge-triggered interrupts.
		
		pGPIO->GPIO_IM |= ( 1<<PinNumber );				//	Disable the interrupt mask to re-enable the interrupts.
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
	SYSCTL->SRGPIO |=  (1<<GPIOPort);				// Reset the port by setting the appropriate bit
	SYSCTL->SRGPIO &= ~(1<<GPIOPort);				// The bit is cleared so that it doesn't always remain in reset state.
	
	GPIO_ClockControl(GPIOPort,DISABLE);		// Disable the clock.
}
	
	

/******************************************************************************************************************
*	@ReadFromPin()																																																	*
*	@brief				-	This function reads data from a GPIO pin																												*
* @pin					-	This is the pin from which we have to read the data																							*
* @return				-	Digital value on the specified pin.																															*
******************************************************************************************************************/
uint8_t	ReadFromPin(uint8_t pin)
{
	return (	getPortAddr(pin,APB_BUS)->GPIO_DATA	&	(1<<getPinNumber(pin)) )?1:0;
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
	return ( getPortAddrFromPortName(GPIOPort,APB_BUS) )->GPIO_DATA;
	// The above statement is equivalent to return pGPIOx->GPIO_DATA;
}
	
	

/******************************************************************************************************************
*	@WriteToPin()																																																		*
*	@brief				-	This function writes the given value to a GPIO pin																							*
* @pin					-	This is the pin to which we have to write the data																							*
*	@Value				-	Value which is to be written to the pin.																												*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void			WriteToPin(uint8_t pin, uint8_t Value)
{
	if(Value == PIN_SET)					getPortAddr(pin,APB_BUS)->GPIO_DATA |=	( 1<<getPinNumber(pin) );
	else if(Value == PIN_RESET)		getPortAddr(pin,APB_BUS)->GPIO_DATA &= ~( 1<<getPinNumber(pin) );
	
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
void			WriteToPort(uint8_t GPIO_PORT, uint8_t Values)
{
	( getPortAddrFromPortName(GPIO_PORT,APB_BUS) )->GPIO_DATA = Values;
	//	The above statement is equivalent to pGPIOx->GPIO_DATA = Values
}
	
	

/******************************************************************************************************************
*	@ToggleGPIOPin()																																																*
*	@brief				-	This function toggles the state of a GPIO pin																										*
* @pin					-	This is the pin which needs to be toggled.																											*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void			ToggleGPIOPin(uint8_t pin)
{
	getPortAddr(pin,APB_BUS)->GPIO_DATA ^= (1<<getPinNumber(pin));
	//	The above statement is equivalent to pGPIOx->GPIO_DATA ^= (1<<PinNumber)
}



/******************************************************************************************************************
*	@DigitalPin()																																																		*
*	@brief				-	This function configures a GPIO pin in Digital mode																							*
* @pin					-	This variable holds the pin number which needs to be configured.																*
*	@IOmode				-	Input/Output mode.																																							*
*	@opType				-	Pull Up, Pull Down, or Open Drain mode.																													*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void	DigitalPin(uint8_t pin, uint8_t IOmode, uint8_t opType)
{
	GPIO_Init(pin,IOmode,NoAlternateFunction,opType,Digital,Eight_mA,NoInterrupt);
}



/******************************************************************************************************************
*	@AnalogPin()																																																		*
*	@brief				-	This function configures a GPIO pin in Analog mode																							*
* @pin					-	This variable holds the pin number which needs to be configured.																*
*	@IOmode				-	Input/Output mode.																																							*
*	@opType				-	Pull Up, Pull Down, or Open Drain mode.																													*
* @return				-	Nothing (void).																																									*
******************************************************************************************************************/
void	AnalogPin(uint8_t pin, uint8_t IOmode, uint8_t opType)
{
	GPIO_Init(pin,IOmode,NoAlternateFunction,opType,Analog,Eight_mA,NoInterrupt);
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

	GPIO_Init(pin,IN,NoAlternateFunction,PullUp,Digital,Eight_mA,triggerMode);
	
	/****************************************************************************************************************
	*	Specify the address of the ISR, and Enable the interrupt by setting the appropriate bit in the NVIC Enable		*
	*	register (in our case, EN0).																																									*
	****************************************************************************************************************/
	switch(PortName)
	{
		case GPIO_PORT_A:	GPIOA_INT_PIN = PinNumber;
											Nvic->EN[0] |= ( 1 << NVIC_EN0_GPIOA );
											break;
		case GPIO_PORT_B:	GPIOB_INT_PIN = PinNumber;
											Nvic->EN[0] |= ( 1 << NVIC_EN0_GPIOB );
											break;
		case GPIO_PORT_C:	GPIOC_INT_PIN = PinNumber;
											Nvic->EN[0] |= ( 1 << NVIC_EN0_GPIOC );
											break;
		case GPIO_PORT_D:	GPIOD_INT_PIN = PinNumber;
											Nvic->EN[0] |= ( 1 << NVIC_EN0_GPIOD );
											break;
		case GPIO_PORT_E:	GPIOE_INT_PIN = PinNumber;
											Nvic->EN[0] |= ( 1 << NVIC_EN0_GPIOE );
											break;
		case GPIO_PORT_F:	GPIOF_INT_PIN = PinNumber;
											Nvic->EN[0] |= ( 1 << NVIC_EN0_GPIOF );
											break;
	}
}



/******************************************************************************************************************
*	@getAltFnNum()																																																	*
*	@brief				-	This function returns the number(index) of an alternate function																*
* @AltFnName		-	This is the name of the Alternate function for which we need to find the index									*
* @return				-	Alternate Function Number.																																			*
******************************************************************************************************************/
uint8_t		getAltFnNum(uint8_t AltFnName)
{
	switch(AltFnName)
	{
		case UART0:
		case UART2:
		case UART3:
		case UART4:
		case UART5:
		case UART6:
		case UART7:
		case SSI3:	return 1;
		case UART1:
		case SSI0:
		case SSI1:
		case SSI2:	return 2;
		case CAN0:
		case I2C0:
		case I2C1:
		case I2C2:
		case I2C3:	return 3;
		default:		return 0;
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

	GPIO_Init(pin,IN,NoAlternateFunction,PullUp,Digital,Eight_mA,triggerMode);
	
	/****************************************************************************************************************
	*	Specify the address of the ISR, and Enable the interrupt by setting the appropriate bit in the NVIC Enable		*
	*	register (in our case, EN0).																																									*
	****************************************************************************************************************/
	switch(PortName)
	{
		case GPIO_PORT_A:	GPIOA_INT_PIN = PinNumber;
											ExceptionHandlers->_GPIOA = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<0;
											break;
		case GPIO_PORT_B:	GPIOB_INT_PIN = PinNumber;
											ExceptionHandlers->_GPIOB = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<1;
											break;
		case GPIO_PORT_C:	GPIOC_INT_PIN = PinNumber;
											ExceptionHandlers->_GPIOC = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<2;
											break;
		case GPIO_PORT_D:	GPIOD_INT_PIN = PinNumber;
											ExceptionHandlers->_GPIOD = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<3;
											break;
		case GPIO_PORT_E:	GPIOE_INT_PIN = PinNumber;
											ExceptionHandlers->_GPIOE = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<4;
											break;
		case GPIO_PORT_F:	GPIOF_INT_PIN = PinNumber;
											ExceptionHandlers->_GPIOF = (uint32_t)isr_func;
											Nvic->EN[0] |= 1<<30;
											break;
	}
}


