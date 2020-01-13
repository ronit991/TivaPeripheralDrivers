#include "TM4C123xxSSI_DRIVER.h"
#include <math.h>



/******************************************************************************************************************
*																				Pins Available for SSI functions																					*
*																																																									*
*		 SSIx				CLK				SS				Rx				Tx		Comments																											*
*																																																									*
*			0					PA2				PA3				PA4				PA5																																	*
*			1					PF2				PF3				PF0				PF1																																	*
*			1					PD0				PD1				PD2				PD3		(These pins aren't used for SSI1 in this driver)							*
*			2					PB4				PB5				PB6				PB7																																	*
*			3					PD0				PD1				PD2				PD3																																	*
******************************************************************************************************************/



/******************************************************************************************************************
*																					APIs Supported by this Drivier																					*
*																																																									*
*		void SSIClockControl()	-	Enable/Disable clock for SSI modules.																								*
*		void SSIInit()					-	Initialize an SSI module.																														*
*		void SSIDeInit()				-	De-Initialize(Reset and Disable) an SSI module.																			*
*		void SSISendData()			-	Sends data using one of the available SSI modules.																	*
******************************************************************************************************************/



/******************************************************************************************************************
*	@SSIClockControl																																																*
* @brief			-	This function is used to enable or disable clock for a particular SSI module.											*
*	@SSIx				- Name of the SSI module for which clock needs to be enabled or disabled.														*
*	@EnOrDi			- This variable speifies whether we have to enable or disable the clock.														*
*								Use (I) ENABLE or (II) DISABLE macros for this variable for better readability.										*
*								These macros are defined in TM4C123xx.h header file under the section "Miscellaneous macros and		*
*								shorthands".																																											*
******************************************************************************************************************/
void SSIClockControl(uint8_t SSIx,uint8_t	EnOrDi)
{
	if(EnOrDi == ENABLE)
		switch(SSIx)
		{
			case SSI0:	SSI0_PCLK_EN();		break;
			case SSI1:	SSI1_PCLK_EN();		break;
			case SSI2:	SSI2_PCLK_EN();		break;
			case SSI3:	SSI3_PCLK_EN();		break;
		}
	else
		switch(SSIx)
		{
			case SSI0: SSI0_PCLK_DIS();		break;
			case SSI1: SSI1_PCLK_DIS();		break;
			case SSI2: SSI2_PCLK_DIS();		break;
			case SSI3: SSI3_PCLK_DIS();		break;
		}
}



/******************************************************************************************************************
*	@SSIInit()																																																			*
*	@brief						-	This function Initializes an SSI module.																										*
* @SSIx							-	This is the name of the SSI module which needs to be initialized.														*
*	@DeviceMode				-	Used to specify Master or Slave mode.																												*
* @ClockSource			-	Used to select the clock source for the SSI module.																					*
*	@ClockPrescalar		-	Even number by which the clock is divided i.e. prescaled.																		*
*	@SerialClockRate	-	SCR is used to configure the SSI clock frequency.																						*
*	@Phase						-	0 => Data capture on first clk edge,	1=> Data capture on second clk edge										*
*	@Polarity					-	0 => Steady Low SSI Clk,	1 => Steady High SSI Clk																					*
*											Phase and Polarity jointly determine the instant at which data is captured.									*
*	@FrameFormat			-	Format of data transfer (Freescale SPI, MICROWIRE, TI SSI Format).													*
*	@DataSize					-	Size of data frame in bits.																																	*
*																																																									*
*	@Note							-	See Pg No. 956 (Section 15.4) for detailed steps on initialization and Configuration.				*
******************************************************************************************************************/
void SSIInit(uint8_t SSIx, uint8_t DeviceMode, uint8_t ClockSource, uint8_t ClockPrescalar, uint8_t SerialClockRate, uint8_t Phase, uint8_t Polarity, uint8_t FrameFormat, uint8_t DataSize)
{
	ssi_reg*	pSSI;
	uint8_t gpio_pins[4];				//	This array stores the names of pins which need to be configured as SSI pins {Clk,SS,Rx,Tx}
	
	// Step1,2 :	Enable the module and provide clock to the appropriate SSI module
	SSIClockControl(SSIx,ENABLE);
	
	switch(SSIx)
	{
		case SSI0:	// configure pins for SSI0
								gpio_pins[0] = PA2;				//	CLK
								gpio_pins[1] = PA3;				//	SS
								gpio_pins[2] = PA4;				//	Rx
								gpio_pins[3] = PA5;				//	Tx
								pSSI = pSSI0;							//	Pointer to SSI0
								break;
		case SSI1:	// configure pins for SSI1
								gpio_pins[0] = PF2;				//	CLK
								gpio_pins[1] = PF3;				//	SS
								gpio_pins[2] = PF0;				//	Rx
								gpio_pins[3] = PF1;				//	Tx
								pSSI = pSSI1;							//	Pointer to SSI1
								break;
		case SSI2:	// configure pins for SSI2
								gpio_pins[0] = PB4;				//	CLK
								gpio_pins[1] = PB5;				//	SS
								gpio_pins[2] = PB6;				//	Rx
								gpio_pins[3] = PB7;				//	Tx
								pSSI = pSSI2;							//	Pointer to SSI2
								break;
		case SSI3:	// configure pins for SSI3
								gpio_pins[0] = PD0;				//	CLK
								gpio_pins[1] = PD1;				//	SS
								gpio_pins[2] = PD2;				//	Rx
								gpio_pins[3] = PD3;				//	Tx
								pSSI = pSSI3;							//	Pointer to SSI3
								break;
	}
	pSSI->SSI_CR[1] &= ~(1<<SSI_CR1_SSE);		//	Clear the SSE bit in the SSICR1 register before configuring SSI.
	
	for(int i = 0; i<4; i++)
	{
		//GPIO_Init(pin, Dir, AltFn, OpType, Mode, DriveStrength, Trigger);
		GPIO_Init(gpio_pins[i],( (i==2)?IN:OUT ),getAltFnNum(SSIx),PullUp,Digital,Eight_mA,NoInterrupt);
	}
	WriteToPin(gpio_pins[2],PIN_RESET);			// Pull SS Pin high so that the slave isn't activated.
	
	/****************************************************************************************************************
	*	To select whether the SSI is a master or slave:																																*
	*		a.	For master operations,									 set the SSICR[1] register to 0x0000.0000												*
	*		b.	For slave  operations (output enabled),  set the SSICR[1] register to 0x0000.0004												*
	*		c.	For slave  operations (output disabled), set the SSICR[1] register to 0x0000.000C												*
	****************************************************************************************************************/
	switch(DeviceMode)
	{
		case SSI_Master_Mode:				pSSI->SSI_CR[1] = 0x00000000;				break;
		case SSI_Slave_Mode_OutEn:	pSSI->SSI_CR[1] = 0x00000004;				break;
		case SSI_Slave_Mode_OutDis:	pSSI->SSI_CR[1] = 0x0000000C;				break;
	}
	
	// Configure Clock Source
	switch(ClockSource)
	{
		case SSI_Clk_SystemClock:		pSSI->SSI_CC &= 0xFFFFFFF0;		break;		//	System Clock
		case SSI_Clk_PIOSC:					pSSI->SSI_CC |= 0x00000005;		break;		//	Precision Internal Oscillator
		default:										return;
	}
		
	
	// Configure Prescale Divider
	pSSI->SSI_CPSR |= ClockPrescalar	<<	0;
	
	// Configure SSI_CR0 for CLK rate, Phase, Polarity, ProtocolMode and Data Size
	pSSI->SSI_CR[0] |= SerialClockRate	<<	SSI_CR0_SCR;
	pSSI->SSI_CR[0] |= Phase						<<	SSI_CR0_SPH;
	pSSI->SSI_CR[0] |= Polarity					<<	SSI_CR0_SPO;
	pSSI->SSI_CR[0] |= FrameFormat			<<	SSI_CR0_FRF;
	pSSI->SSI_CR[0] |= DataSize					<<	SSI_CR0_DSS;
	
	// Configure SSI module for DMA (optional)
	//	<insert code for dma configuration>
	
	pSSI->SSI_CR[1] |= 1<<SSI_CR1_SSE;				// Enable SSI port.
}



/******************************************************************************************************************
*	@SSIDeInit()																																																		*
*	@brief				-	This function De-Initializes(Reset and Disable) an SSI module.																	*
* @SSIx					-	This is the name of the SSI module which needs to be de-initialized.														*
*																																																									*
*	@Note					- To reset a SSI module, the corresponding bit in the SRSSI register needs to be set. Clock to		*
*									the module is then disabled to save power, and prevent access to the module.										*
******************************************************************************************************************/
void SSIDeInit(uint8_t SSIx)
{
	SYSCTL->SRSSI |=	1<<(SSIx-6);						//	Reset the SSI Module by setting the appropriate bit in the SRSSI register.
	SYSCTL->SRSSI &=	~( 1<<(SSIx-6) );				//	Clear the bit so that the module doesn't always remain in the reset state.
	SSIClockControl(SSIx,DISABLE);						//	Disable clock to the module to save power.
}



/******************************************************************************************************************
* @SSIStart()																																																			*
* @brief											-	This function initializes an SSI module with default settings and a 2 MHz SSI			*
*																Clock. Additionally, interrupt delivery from the SSI module to the interrupt			*
*																controller(NVIC) can be enabled or disabled as required.													*
* @SSIx												-	This is the name of the SSI module which needs to be initialized.									*
*	@DeviceMode									-	Used to specify Master or Slave mode.																							*
*	@InterruptsNeedToBeEnabled	- Specifies whether interrupts should be enabled or not.														*
*																																																									*
* @Note												- Default settings for SSI modules:																									*
*																1. Clock Source			-	Precision Internal Oscillator (16 MHz)											*
*																2. Clock Prescalar	-	2																														*
*																3. Serial Clk Rate	-	3																														*
*																4. Phase						-	0																														*
*																5. Polarity					-	0																														*
*																6. Frame Format			-	Freescale SPI format																				*
*																7. Data Size				-	16-bit																											*
*	In case of an ssi module name mismatch, this function will break out, and no ssi module will be configured.			*
******************************************************************************************************************/
void SSIStart(uint8_t SSIx,uint8_t DeviceMode, uint8_t InterruptsNeedToBeEnabled)
{
	if(InterruptsNeedToBeEnabled)
	{
		ssi_reg* pSSI;
		switch(SSIx)
		{
			case	SSI0:			Nvic->EN[0] |= ( 1 << NVIC_EN0_SSI0 );		pSSI = pSSI0;	 	break;
			case	SSI1:			Nvic->EN[1] |= ( 1 << NVIC_EN1_SSI1 );		pSSI = pSSI1;	 	break;
			case	SSI2:			Nvic->EN[1] |= ( 1 << NVIC_EN1_SSI2 );		pSSI = pSSI2;	 	break;	
			case	SSI3:			Nvic->EN[1] |= ( 1 << NVIC_EN1_SSI3 );		pSSI = pSSI3;	 	break;
			default:				return;									//	Break out of the function in case of a mismatch.
		}
		
		/**************************************************************************************************************
		*	The Interrupt Mode macros (defined in the SSI driver header file) have integer values equal to their bit		*
		*	position in the Interrupt Mask register (SSIIM) plus one. To enable an interrupt, corresponding mask should *
		*	be disabled by setting the bit in SSIIM register. To get the bit position, subtract one from the interrupt	*
		*	mode variable (InterruptsNeedToBeEnabled).																																	*
		**************************************************************************************************************/
		uint8_t IntrMaskPosition = ( InterruptsNeedToBeEnabled - 1 );
		
		pSSI->SSI_IM |= ( 1 << IntrMaskPosition );
	}
	
	//SSIInit(SSIx, DeviceMode, ClockSource, ClockPrescalar, SerialClockRate, Phase, Polarity, FrameFormat, DataSize)
	SSIInit(SSIx, DeviceMode, SSI_Clk_PIOSC, 2, 3, 0, 0, SSI_FreescaleFormat, SSI_Data_16bit);
}



/******************************************************************************************************************
*	@SSISendData()																																																	*
*	@brief				-	This function is used to transmit/send data over an SSI channel.																*
* @SSIx					-	This is the name of the SSI module over which, data has to be sent.															*
*	@DataBuf			-	Data bits which need to be transmitted.																													*
*	@Len					-	Data Size, or the length of Data bits which need to be sent.																		*
*																																																									*
*	@Note					-	This function does not care if the SSI module is properly initialized or not. Make sure that		*
*									the SSI module is already configured as needed otherwise data transmission might not occur.			*
*									Also, it might generate bus faults if the clock is disabled.																		*
*	@Note2				-	In case of a mismatch of module name, or incorrect data length, the function does not proceed		*
*									further and breaks out when an anomaly is detected.																							*
******************************************************************************************************************/
void SSISendData(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len)
{
	ssi_reg* pSSI;
	uint8_t SS_pin;
	switch(SSIx)
	{
		case SSI0:	pSSI = pSSI0;			SS_pin = SSI0_SS_PIN;		 break;
		case SSI1:	pSSI = pSSI1;			SS_pin = SSI1_SS_PIN;		 break;
		case SSI2:	pSSI = pSSI2;			SS_pin = SSI2_SS_PIN;		 break;
		case SSI3:	pSSI = pSSI3;			SS_pin = SSI3_SS_PIN;		 break;
		default:		return;											//	Break out of the function in case of a mismatch.
	}
	
	if(Len == 0)	return;											//	Break out of the function in case of a mismatch.
	else
	{
		uint8_t n = ceil( Len/16.0 );						//	Tx count (no of 16 bit data packets that are to be sent)
		do
		{
			/************************************************************************************************************
			*	First bit of status register shows whether the Tx buffer is empty or not.																	*
			*	1 -> Tx buffer is empty.	0 -> Tx buffer is not empty.																										*
			************************************************************************************************************/
			uint8_t TxNotEmpty;
			do
			{
				TxNotEmpty = ( pSSI->SSI_SR & (1<<SSI_SR_TFE) )?0:1;
			}while( TxNotEmpty );									//	Wait until the Tx buffer becomes empty.
			uint16_t currentData = *DataBuf;
			pSSI->SSI_DR |= currentData<<0;				//	Insert data into the Tx buffer by writing it to SSIDR register.
			WriteToPin(SS_pin,PIN_RESET);					//	Pull the SS pin low, to activate the slave.
			
			while(pSSI->SSI_SR & 1<<SSI_SR_BSY);	//	Wait while the SSI module is busy sending the data.
			
			WriteToPin(SS_pin,PIN_SET);						//	Pull SS Pin high to de-activate the slave.
			DataBuf++;														//	Step the pointer to the next data set.
			n--;																	//	Decrease the Tx count.
		}while(n>0);														//	Do this until the Tx count becomes zero.
	}
}



/******************************************************************************************************************
*	@SSIRecvData()																																																	*
*	@brief				-	This function is used to recevie data over an SSI channel.																			*
* @SSIx					-	This is the name of the SSI module from which, data has to be received.													*
*	@DataBuf			-	Pointer to data buffer which will be used to hold the received data.														*
*	@Len					-	Data Size, or the length of Data bits which need to be received.																*
*																																																									*
*	@Note					-	This function does not care if the SSI module is properly initialized or not. Make sure that		*
*									the SSI module is already configured as needed otherwise no data will be received.							*
*									Also, it might generate bus faults if the clock is disabled.																		*
*	@Note2				-	In case of a mismatch of module name, or incorrect data length, the function does not proceed		*
*									further and breaks out when an anomaly is detected.																							*
******************************************************************************************************************/
void SSIRecvData(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len)
{
	ssi_reg* pSSI;
	switch(SSIx)
	{
		case SSI0:	pSSI = pSSI0;		 break;
		case SSI1:	pSSI = pSSI1;		 break;
		case SSI2:	pSSI = pSSI2;		 break;
		case SSI3:	pSSI = pSSI3;		 break;
		default:		return;											//	Break out of the function in case of a mismatch.
	}
	
	if(Len == 0)	return;											//	Break out of the function in case of a mismatch.
	else
	{
		
		uint8_t n = ceil( Len/16.0 );						// Rx count (no of 16 bit data packets that are to be received)
		do
		{
			/************************************************************************************************************
			*	Fourth bit (SSI_SR_RFF) of status register shows whether the Rx buffer is full or not.										*
			*	1 -> Rx buffer is full.		0 -> Rx buffer is not full.																											*
			************************************************************************************************************/
			uint8_t RxNotFull;
			do
			{
				RxNotFull = ( pSSI->SSI_SR & (1<<SSI_SR_RFF) )?0:1;
			}while( RxNotFull );									//	Wait until the Rx buffer isn't full.
			
			*DataBuf = (uint16_t)pSSI->SSI_DR;
			/************************************************************************************************************
			*	Pick data from SSIDR register, and put it into the Rx buffer. NOTE: SSI_DR register is 32-bit register,		*
			*	but Rx shift register is of 16-bits. Rest of the 16 bits in the SSI_DR register are reserved. Data, of		*
			*	our concern, lies in the first 16-bits. So we convert the value in the SSI_DR register to uint16_t. This	*
			*	discards the higher 16 bits, and stores the remaining bits in the data variable, pointed by DataBuf.			*
			************************************************************************************************************/
			
			DataBuf++;														//	Step the pointer for the next data set.
			n--;																	//	Decrease the Rx count.
		}while(n>0);														//	Do this until the Rx count becomes zero.
	}
}
