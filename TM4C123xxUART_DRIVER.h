/******************************************************************************************************************
*	@file			-	TM4C123xxUART_DRIVER.h																																							*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains prototypes of UART Driver APIs. Bit position macros and shorthands which are used by the			*
*	UART Driver APIs are also defined here.																																					*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/

#ifndef TM4C123XXUART_DRIVER_H
#define TM4C123XXUART_DRIVER_H

#include "TM4C123xx.h"

/******************************************************************************************************************
*																								Bit Position Macros																								*
******************************************************************************************************************/
// Data Register
#define UART_DR_FE				8				//	Framing Error
#define UART_DR_PE				9				//	Parity Error
#define UART_DR_BE				10			//	Break Error
#define UART_DR_OE				11			//	Overrun Error

// Receive Status / Error Clear Register
#define UART_RSR_FE				0				//	Framing Error
#define UART_RSR_PE				1				//	Parity Error
#define UART_RSR_BE				2				//	Break Error
#define UART_RSR_OE				3				//	Overrun Error

// Flag Register
#define UART_FR_CTS				0				//	Clear To Send
#define UART_FR_BUSY			3				//	UART Busy
#define UART_FR_RXFE			4				//	Receive FIFO Empty
#define UART_FR_TXFF			5				//	Transmit FIFO Full
#define UART_FR_RXFF			6				//	Receive FIFO Full
#define UART_FR_TXFE			7				//	Transmit FIFO Empty

// Line Control Register
#define UART_LCRH_BRK			0				//	Send Break
#define UART_LCRH_PEN			1				//	Parity Enable
#define UART_LCRH_EPS			2				//	Even Parity Select
#define UART_LCRH_STP2		3				//	Two Stop Bits Select
#define UART_LCRH_FEN			4				//	Enable Tx/Rx FIFOs
#define UART_LCRH_WLEN		5				//	Word Length
#define UART_LCRH_SPS			7				//	Stick Parity Select

// UART Control Register
#define UART_CTL_UARTEN		0				//	UART Enable
#define UART_CTL_SIREN		1				//	SIR Enable
#define UART_CTL_SIRLP		2				//	SIR Low-Power Mode
#define UART_CTL_SMART		3				//	ISO 7816 Smart Card Support
#define UART_CTL_EOT			4				//	End of Transmission
#define UART_CTL_HSE			5				//	High-Speed Enable
#define UART_CTL_LBE			7				//	Loopback Enable
#define UART_CTL_TXE			8				//	Transmit Enable
#define UART_CTL_RXE			9				//	Receive Enable
#define UART_CTL_RTS			11				//	Request To Send
#define UART_CTL_RTSEN		14				//	Enable Request-To-Send
#define UART_CTL_CTSEN		15				//	Enable Clear-To-Send

// Interrupt Mask Register
#define UART_IM_CTS				1					//	Clear-To-Send Modem Interrupt
#define UART_IM_RX				4					//	Receive Interrupt
#define UART_IM_TX				5					//	Transmit Interrupt
#define UART_IM_RT				6					//	Recevie Time-out
#define UART_IM_FE				7					//	Framing Error
#define UART_IM_PE				8					//	Parity Error
#define UART_IM_BE				9					//	Break Error
#define UART_IM_OE				10				//	Overrun Error
#define UART_IM_9BIT			12				//	9-Bit Mode

// Raw Interrupt Status Register
#define UART_RIS_CTS			1					//	Clear-To-Send Modem Interrupt
#define UART_RIS_RX				4					//	Receive Interrupt
#define UART_RIS_TX				5					//	Transmit Interrupt
#define UART_RIS_RT				6					//	Recevie Time-out
#define UART_RIS_FE				7					//	Framing Error
#define UART_RIS_PE				8					//	Parity Error
#define UART_RIS_BE				9					//	Break Error
#define UART_RIS_OE				10				//	Overrun Error
#define UART_RIS_9BIT			12				//	9-Bit Mode

// Masked Interrupt Status Register
#define UART_MIS_CTS			1					//	Clear-To-Send Modem Interrupt
#define UART_MIS_RX				4					//	Receive Interrupt
#define UART_MIS_TX				5					//	Transmit Interrupt
#define UART_MIS_RT				6					//	Recevie Time-out
#define UART_MIS_FE				7					//	Framing Error
#define UART_MIS_PE				8					//	Parity Error
#define UART_MIS_BE				9					//	Break Error
#define UART_MIS_OE				10				//	Overrun Error
#define UART_MIS_9BIT			12				//	9-Bit Mode

// Interrupt Clear Register
#define UART_ICR_CTS			1					//	Clear-To-Send Modem Interrupt
#define UART_ICR_RX				4					//	Receive Interrupt
#define UART_ICR_TX				5					//	Transmit Interrupt
#define UART_ICR_RT				6					//	Recevie Time-out
#define UART_ICR_FE				7					//	Framing Error
#define UART_ICR_PE				8					//	Parity Error
#define UART_ICR_BE				9					//	Break Error
#define UART_ICR_OE				10				//	Overrun Error
#define UART_ICR_9BIT			12				//	9-Bit Mode

// DMA Control Register
#define UART_DMACTL_RXDMAE		0			//	Rx DMA Enable
#define UART_DMACTL_TXDMAE		1			//	Tx DMA Enable
#define UART_DMACTL_DMAERR		2			//	DMA on Error

// Peripheral Properties Register
#define UART_PP_SC				0					//	Smart Card Support
#define UART_PP_NB				1					//	9-Bit Support



/******************************************************************************************************************
*															Miscellaneous macros, shorthands and Global variables																*
******************************************************************************************************************/

/******************************************************************************************************************
	@UARTTransferPending
	Each bit of this variable corresponds to the UART of that index. A bit set in an index implies that some data
	transfer is pending for that UART (by interrupts).
	Ex: If bit 5 of this variable is set => UART5 has some pending data transfer.
******************************************************************************************************************/
extern uint8_t UARTTransferPending;


/******************************************************************************************************************
	@UARTTransferBuffer
	This array stores pointer to data buffers which can be used by interrupt handlers.
******************************************************************************************************************/
extern uint8_t* UARTTransferBuffer[8];


/******************************************************************************************************************
	@UARTTransferLength
	This array stores the lengths (in bytes) of data buffers of each UART peripheral. These are used by interrupt
	handlers.
******************************************************************************************************************/
extern int8_t UARTTransferLength[8];

/******************************************************************************************************************
	@BaudRateArray
	This array contains the standard UART Baud rates (divided by 100)
	The standard baud rates are: 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200.
	So the contents of this array are : 12, 24, 48, 96, 192, 384, 576, 1152.
******************************************************************************************************************/
extern uint16_t BaudRateArray[8];

// @BaudRate
#define BaudRate_1200					0
#define BaudRate_2400					1
#define BaudRate_4800					2
#define BaudRate_9600					3
#define BaudRate_19200				4
#define BaudRate_38400				5
#define BaudRate_57600				6
#define BaudRate_115200				7

// @ParityControl
#define DisableParity					0
#define EvenParity						1
#define	OddParity							2

// @WordLength
#define _5bit_WordLength			0
#define _6bit_WordLength			1
#define _7bit_WordLength			2
#define _8bit_WordLength			3

// @HWFlowControl
#define EnableHWFlowControl				ENABLE
#define DisableHWFlowControl			DISABLE

// @NoOfStopBits
#define OneStopBit						0
#define TwoStopBits						1

// @FIFOControl
#define EnableFIFO						ENABLE
#define DisableFIFO						DISABLE


/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*	Below are the prototypes for driver APIs																																				*
*
******************************************************************************************************************/
void UARTClockControl(uint8_t UARTx, uint8_t ENorDI);
void UARTInit(uint8_t UARTx, uint8_t WordLength, uint8_t BaudRate, uint8_t ParityMode, uint8_t NoOfStopBits, uint8_t FIFOControl);
void UARTDeInit(uint8_t UARTx);

void UARTSend(uint8_t UARTx, uint8_t *TxBuf, int8_t Len);
void UARTRecv(uint8_t UARTx, uint8_t *RxBuf, int8_t Len);

void UARTSendByte(uint8_t UARTx, uint8_t TxData);
uint8_t UARTRecvByte(uint8_t UARTx);

uint8_t UARTSendIT(uint8_t UARTx, uint8_t *TxBuf, uint8_t Len);
uint8_t UARTRecvIT(uint8_t UARTx, uint8_t *RxBuf, uint8_t Len);
void UARTSendIT_H(uint8_t UARTx);
void UARTRecvIT_H(uint8_t UARTx);


UART_Reg* UARTGetAddress(uint8_t UARTx);
uint8_t UARTGetTxPin(uint8_t UARTx);
uint8_t UARTGetRxPin(uint8_t UARTx);
void WaitWhileUARTisBusy(UART_Reg* pUARTx);

#endif

/*
void UARTClockControl();				[X]
void UARTInit();								[X]
void UARTDeInit();							[X]
void UARTSend();								[X]
void UARTRecv();								[X]
void UARTSendByte();						[X]
uint8_t UARTRecvByte();					[X]
void UARTSendIT();							[O]
void UARTRecvIT();							[O]
UART_Reg* UARTGetAddress();			[X]
uint8_t UARTGetTxPin();					[X]
uint8_t UARTGetRxPin();					[X]
void WaitWhileUARTisBusy();			[X]

*/

