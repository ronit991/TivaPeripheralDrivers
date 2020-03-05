/******************************************************************************************************************
*	@file			-	TM4C123xxUART_DRIVER.c																																							*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains definition of UART Driver APIs.																															*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/

// DETAILS OF DRIVER APIs - HERE



#include "TM4C123xxUART_DRIVER.h"


// GLOBAL VARIABLES
uint16_t BaudRateArray[8] = {12, 24, 48, 96, 192, 384, 576, 1152};



/******************************************************************************************************************
*	@UARTClockControl()																																															*
* @brief			-	This function is used to enable or disable clock for a particular SSI module.											*
*	@SSIx				- Name of the UART module for which clock needs to be enabled or disabled.													*
*	@EnOrDi			- This variable speifies whether we have to enable or disable the clock.														*
*								Use (I) ENABLE or (II) DISABLE macros for this variable.																					*
******************************************************************************************************************/
void UARTClockControl(uint8_t UARTx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
		switch(UARTx)
		{
			case UART0:		UART0_PCLK_EN();				return;
			case UART1:		UART1_PCLK_EN();				return;
			case UART2:		UART2_PCLK_EN();				return;
			case UART3:		UART3_PCLK_EN();				return;
			case UART4:		UART4_PCLK_EN();				return;
			case UART5:		UART5_PCLK_EN();				return;
			case UART6:		UART6_PCLK_EN();				return;
			case UART7:		UART7_PCLK_EN();				return;
			
			default: return;
		}
	else
		switch(UARTx)
		{
			case UART0:		UART0_PCLK_DIS();				return;
			case UART1:		UART1_PCLK_DIS();				return;
			case UART2:		UART2_PCLK_DIS();				return;
			case UART3:		UART3_PCLK_DIS();				return;
			case UART4:		UART4_PCLK_DIS();				return;
			case UART5:		UART5_PCLK_DIS();				return;
			case UART6:		UART6_PCLK_DIS();				return;
			case UART7:		UART7_PCLK_DIS();				return;
			
			default: return;
		}
}



/******************************************************************************************************************
*	@UARTInit()																																																			*
*	@brief				-	This function Initializes an UART module.																												*
*	@UARTx				- Name of the UART Module.																																				*
* @WordLength		- Length of the data bits to be sent at a time.																										*
* @BaudRate			- Rate of data transmission.																																			*
*	@ParityMode		-	Even/Odd/No Parity.																																							*
*																																																									*
*	@Note					->	See Pg No. 902 (Section 14.4) for detailed steps on Initialization and Configuration.					*
*								->	Use standard macros defined in the UART header file for all the four variables.								*
******************************************************************************************************************/
void UARTInit(uint8_t UARTx, uint8_t WordLength, uint8_t BaudRate, uint8_t ParityMode)
{
	uint8_t TXPIN = UARTGetTxPin(UARTx);
	uint8_t RXPIN = UARTGetRxPin(UARTx);
	
	uint8_t TxPinNum = getPinNumber(TXPIN);
	uint8_t RxPinNum = getPinNumber(RXPIN);
	uint8_t UartPins = ( (1<<TxPinNum) | (1<<RxPinNum) );
	
	GPIO_reg* pGPIO = getPortAddr(TXPIN, APB_BUS);
	UART_Reg* pUART = UARTGetAddress(UARTx);
	
	UARTClockControl(UARTx, ENABLE);									// Step 1 - Section 14.4: Enable clock to the UART Module.
	
	GPIO_ClockControl(getPortName(TXPIN), ENABLE);		// Step 2 - Section 14.4: Enable clock to the appropriate GPIO Module.
	
	pGPIO->GPIO_AFSEL |= UartPins;										// Step 3 - Section 14.4: Enable Alternate function for the UART pins.
	pGPIO->GPIO_DR8R |= UartPins;											// Step 4 - Section 14.4: Current control for the UART pins.
	
	// Find out how exactly the slew rate is changing, and accordingly implement the next step.
	//pGPIO->GPIO_SLR |= UartPins;											// Step 4 - Section 14.4 : Slew Rate
	
	// Clear the bit-fields for the appropriate pins in the GPIOPCTL Register.
	pGPIO->GPIO_PCTL &= ~( ( 0xF<<(TxPinNum*4) ) | ( 0xF<<(RxPinNum*4) ) );
	
	// Step 5 - Section 14.4: Set the alternate function number (1 for UART) for the pins.
	pGPIO->GPIO_PCTL |=	 ( ( 0x1<<(TxPinNum*4) ) | ( 0x1<<(RxPinNum*4) ) );
	
	uint8_t CLK_DIV = GET_BIT(pUART->CTL, UART_CTL_HSE)?8:16;
	
	double BRD = (SYS_CLK)/( CLK_DIV*100*BaudRateArray[BaudRate] );
	
	uint16_t iBRD = (uint16_t)BRD;														//	Integer Part of Baud Rate
	uint8_t fBRD = (uint8_t)( (BRD - iBRD)*64 + 0.5 );				//	Fractional Part of Baud Rate Divisor
	
	//	Step Numbers written below, refer to the steps on Pg# 903.
	pUART->CTL CLR_BIT(UART_CTL_UARTEN);					//	Step 1: Disable the UART Module
	pUART->IBRD = iBRD;														//	Step 2:	Write integer part of Baud Rate Divisor
	pUART->FBRD = fBRD;														//	Step 3: Write fractional part of Baud Rate Divisor
	
	// Step 4: Configure LCRH Register
	// Stick Parity Select, Enable FIFOs, & Send Break fields aren't changed right now. It will be implemented later.
	switch(ParityMode)
	{
		case DisableParity:			pUART->LCRH CLR_BIT(UART_LCRH_PEN);
														break;
		case EvenParity:				pUART->LCRH SET_BIT(UART_LCRH_PEN);
														pUART->LCRH SET_BIT(UART_LCRH_EPS);
														break;
		case OddParity:					pUART->LCRH SET_BIT(UART_LCRH_PEN);
														pUART->LCRH CLR_BIT(UART_LCRH_EPS);
														break;
		default:								return;
	}
	
	switch(WordLength)
	{
		case _5bit_WordLength:	pUART->LCRH CLR_BIT(5);
														pUART->LCRH CLR_BIT(6);
														break;
		case _6bit_WordLength:	pUART->LCRH SET_BIT(5);
														pUART->LCRH CLR_BIT(6);
														break;
		case _7bit_WordLength:	pUART->LCRH CLR_BIT(5);
														pUART->LCRH SET_BIT(6);
														break;
		case _8bit_WordLength:	pUART->LCRH SET_BIT(5);
														pUART->LCRH SET_BIT(6);
														break;
		
		default:								return;
	}
	
	// Step 5: Configure Clock Source
	pUART->CC = 0;						//	Set Clock source to system clock. (Set it as 0x5 for PIOSC)
	
	// Step 6: Enable uDMA
	// This will be implemented later.
	
	// Step 7: Enable the UART Module
	pUART->CTL SET_BIT(UART_CTL_UARTEN);
}



/******************************************************************************************************************
*	@UARTDeInit()																																																		*
*	@brief				-	This function De-Initializes(Reset and Disable) an UART module.																	*
* @SSIx					-	Name of the UART module which needs to be de-initialized.																				*
* @return				-	Nothing.																																												*
******************************************************************************************************************/
void UARTDeInit(uint8_t UARTx)
{
	SYSCTL->SRUART SET_BIT((UARTx-14));						//	Reset the UART Module by setting the appropriate bit in the SRUART register.
	SYSCTL->SRUART CLR_BIT((UARTx-14));						//	Clear the bit so that the module doesn't always remain in the reset state.
	// Since UART peripheral name values start from 14 (see TM4C123xx.h), we used (UARTx-14) so that it corresponds to the appropriate bit.
	
	UARTClockControl(UARTx,DISABLE);							//	Disable clock to the module to save power.
}



/*------------------------------------------ DATA TRANSFER FUNCTIONS --------------------------------------------*/



void UARTSendByte(uint8_t UARTx, uint8_t TxData)
{
	UART_Reg* pUART = UARTGetAddress(UARTx);
	
	WaitWhileUARTisBusy(pUART);
	pUART->DR = TxData;
}



uint8_t UARTRecvByte(uint8_t UARTx)
{
	UART_Reg* pUART = UARTGetAddress(UARTx);
	
	WaitWhileUARTisBusy(pUART);
	
	uint8_t RxData;
	RxData = (uint8_t)(pUART->DR);
	
	return RxData;
}
/*---------------------------------------------- HELPER FUNCTIONS -----------------------------------------------*/



/******************************************************************************************************************
* @UARTGetAddress()																																																*
* @UARTx	-	Name of the UART Module whose address is required.																										*
* @return	- Access pointer of the requested UART Module.																													*
*																																																									*
* @Note		- Returns Null if incorrect name is given to the function.																							*
******************************************************************************************************************/
UART_Reg* UARTGetAddress(uint8_t UARTx)
{
	switch(UARTx)
	{
		case UART0:			return pUART0;
		case UART1:			return pUART1;
		case UART2:			return pUART2;
		case UART3:			return pUART3;
		case UART4:			return pUART4;
		case UART5:			return pUART5;
		case UART6:			return pUART6;
		case UART7:			return pUART7;
		
		default:				return NULL;
	}
}



/******************************************************************************************************************
* @UARTGetTxPin()																																																	*
* @UARTx	-	Name of the UART Module whose address is required.																										*
* @return	- Tx Pin of the UART Module.																																						*
*																																																									*
* @Note		- Returns PA1(Tx Pin of UART0) if incorrect name is given to the function.															*
******************************************************************************************************************/
uint8_t UARTGetTxPin(uint8_t UARTx)
{
	switch(UARTx)
	{
		case UART0:				return PA1;
		case UART1:				return PB1;
		case UART2:				return PD7;
		case UART3:				return PC7;
		case UART4:				return PC5;
		case UART5:				return PE5;
		case UART6:				return PD5;
		case UART7:				return PE1;
		
		default:					return PA1;
	}
}

/******************************************************************************************************************
* @UARTGetTxPin()																																																	*
* @UARTx	-	Name of the UART Module whose address is required.																										*
* @return	- Tx Pin of the UART Module.																																						*
*																																																									*
* @Note		- Returns PA1(Tx Pin of UART0) if incorrect name is given to the function.															*
******************************************************************************************************************/
uint8_t UARTGetRxPin(uint8_t UARTx)
{
	switch(UARTx)
	{
		case UART0:				return PA0;
		case UART1:				return PB0;
		case UART2:				return PD6;
		case UART3:				return PC6;
		case UART4:				return PC4;
		case UART5:				return PE4;
		case UART6:				return PD4;
		case UART7:				return PE0;
		
		default:					return PA0;
	}
}



/******************************************************************************************************************
* @WaitWhileUARTisBusy()																																													*
* @pUARTx			-	UART Module Access pointer.																																				*
* @return			-	Nothing(void).																																										*
******************************************************************************************************************/
void WaitWhileUARTisBusy(UART_Reg* pUARTx)
{
	while( GET_BIT(pUARTx->FR, UART_FR_BUSY) );
}
