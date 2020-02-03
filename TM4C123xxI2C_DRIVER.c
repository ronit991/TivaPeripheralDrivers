/******************************************************************************************************************
*	@file			-	TM4C123xxI2C_DRIVER.c																																								*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains definitions of I2C Driver APIs.																															*
*	Don't use 0b0000XXX and 0b1111XXX as device addresses. These are reserved for special purposes as defined in		*
*	I2C specifications.																																															*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/

#include "TM4C123xxI2C_DRIVER.h"

/******************************************************************************************************************
*																					Pins Available for I2C Functions																				*
*		Module				SCL					SDA																																									*
*		I2C 0					PB2					PB3																																									*
*		I2C 1					PA6					PA7																																									*
*		I2C 2					PE4					PE5																																									*
*		I2C 3					PD0					PD1																																									*
******************************************************************************************************************/



// Global variables used by the driver APIs.
// Default device address for all the I2C modules is 0xA1.
uint8_t I2CDeviceAddress[4] = {0xA1, 0xA1, 0xA1, 0xA1};



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*																																																									*
*	I2CClockControl()		-	Enable or Disable clock for an I2C Module.																								*
*	I2CInit()						-	Initialize an I2C Module.																																	*
*	I2CDeInit()					-	Reset and turn off an I2C Module.																													*
*	I2CGetAddress()			-	Get address of an I2C Module.																															*
******************************************************************************************************************/



/******************************************************************************************************************
* @I2CClockControl()																																															*
* @brief	-	Enable or Disable clock for an I2C Module.																														*
* @I2Cx		-	Name of the I2C module.																																								*
*	@EnorDi	-	Specifies whether the clock need to be enabled or disabled.																						*
* @return	-	None.																																																	*
*																																																									*
* @Note		-	If an invalid I2C module name is given to this function, no module will be affected. Access to the		*
*						intended module may generate a bus fault in this case.																								*
******************************************************************************************************************/
uint8_t I2CClockControl(uint8_t I2Cx,uint8_t	EnorDi)
{
	if(EnorDi == ENABLE)
	{
		switch(I2Cx)
		{
			case I2C0:		I2C0_PCLK_EN();				break;
			case I2C1:		I2C1_PCLK_EN();				break;
			case I2C2:		I2C2_PCLK_EN();				break;
			case I2C3:		I2C3_PCLK_EN();				break;
			default:			return 1;							//	Return 1 in case of a mismatch.
		}
	}
	else
	{
		switch(I2Cx)
		{
			case I2C0:		I2C0_PCLK_DIS();				break;
			case I2C1:		I2C1_PCLK_DIS();				break;
			case I2C2:		I2C2_PCLK_DIS();				break;
			case I2C3:		I2C3_PCLK_DIS();				break;
			default:			return 1;							//	Return 1 in case of a mismatch.
		}
	}
	
	return 0;		//	Return 0 in case of successful execution of this function.
}



/******************************************************************************************************************
* @I2CInit()																																																			*
* @brief				-	Initialize an I2C Module.																																				*
* @I2Cx					-	Name of the I2C module.																																					*
*	@SpeedMode		-	Speed mode : Standard, Fast Mode, Fast Mode+, High Speed Mode																		*
*	@ACKControl		-	Enable or Disable Auto Acknowledge mode.																												*
* @UseAsSlave		- Specifies whether to use this device as slave or not. If yes, the address of the device is set	*
*									as given by the I2CxDeviceAddress variable.																											*
* @return				-	None.																																														*
*																																																									*
* @Note		-	If an invalid I2C module name is given to this function, no module will be affected. Access to the		*
*						intended module, at a later stage in the code may generate a bus fault in this case.									*
******************************************************************************************************************/
void I2CInit(uint8_t I2Cx, uint8_t SpeedMode, uint32_t ClkSpeed, uint8_t ACKControl, uint8_t UseAsSlave)
{
	uint8_t Error = I2CClockControl(I2Cx, ENABLE);						//	Step 1 of section 16.4: Enable clock to the module and get error code.
	
	if(Error)		return;																				//	Break out of the function in case of an error.
	
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	
	uint8_t I2C_SCL_PIN = GetSCLPin(I2Cx);
	uint8_t I2C_SDA_PIN = GetSDAPin(I2Cx);
	
	uint8_t I2C_SCL_PIN_NUM = getPinNumber(I2C_SCL_PIN);
	uint8_t I2C_SDA_PIN_NUM = getPinNumber(I2C_SDA_PIN);
	
	GPIO_reg* pGPIO = getPortAddr(I2C_SCL_PIN, APB_BUS);
	
	
	GPIO_ClockControl(getPortName(I2C_SCL_PIN), ENABLE);			//	Step 2 of section 16.4
	
	pGPIO->GPIO_AFSEL SET_BIT( I2C_SCL_PIN_NUM );							//	Step 3 of section 16.4
	pGPIO->GPIO_AFSEL SET_BIT( I2C_SDA_PIN_NUM );
	
	pGPIO->GPIO_ODR SET_BIT( I2C_SDA_PIN_NUM );								//	Step 4 of section 16.4
	pGPIO->GPIO_ODR CLR_BIT( I2C_SCL_PIN_NUM );								//	Also see section 16.3 (Pg 999)
	
	pGPIO->GPIO_PUR SET_BIT( I2C_SCL_PIN_NUM );								//	Enable internal pull up resistor for SCL and SDA signals.
	pGPIO->GPIO_PUR SET_BIT( I2C_SDA_PIN_NUM );
	
	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SCL_PIN_NUM);							//	Step 5 of section 16.4	(The bit positions are cleared first and
	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SDA_PIN_NUM);							//													 then set appropriately)
	
	pGPIO->GPIO_PCTL |= (0x3<<(4*I2C_SCL_PIN_NUM));
	pGPIO->GPIO_PCTL |= (0x3<<(4*I2C_SDA_PIN_NUM));
	
	pI2Cx->MCR SET_BIT(I2C_MCR_MFE);													//	Step 6 of section 16.4
	
	/*Step7 : Set desired spd mode & clock speed*/
	switch(SpeedMode)																					//	Enable/Disable High speed mode
	{
		case I2C_SPEED_MODE_HS: pI2Cx->MTPR SET_BIT( I2C_MTPR_HSE );
														pI2Cx->MCS	SET_BIT( I2C_MCS_HS );
														pI2Cx->PC 	SET_BIT( I2C_PC_HSE );
														break;
		default:								pI2Cx->MTPR CLR_BIT( I2C_MTPR_HSE );
														pI2Cx->MCS	CLR_BIT( I2C_MCS_HS );
														pI2Cx->PC 	CLR_BIT( I2C_PC_HSE );
														break;
	}
	
	uint8_t TimerPRD = ( SYS_CLK/(20*ClkSpeed) ) - 1;					//	Timer Period
	
	pI2Cx->MTPR |= TimerPRD<<I2C_MTPR_TPR;										//	Step 7 of section 16.4
	
	switch(ACKControl)																				//	Enable/Disable Auto ACK
	{
		case I2C_AUTO_ACK_ENABLE:		pI2Cx->MCS SET_BIT( I2C_MCS_ACK );
		case I2C_AUTO_ACK_DISABLE:	pI2Cx->MCS CLR_BIT( I2C_MCS_ACK );
	}
	
	switch(UseAsSlave)
	{
		case YES:		pI2Cx->SCSR SET_BIT(1);
								pI2Cx->SOAR |= ( I2CDeviceAddress[I2Cx - 10]<<0 );				//	Set Device Address
								pI2Cx->SACKCTL SET_BIT(I2C_SACKCTL_OEN);									//	Enable ACK Override.
								pI2Cx->SIMR SET_BIT(I2C_SIMR_DATA);												//	Enable Data Receive Interrupt
								pI2Cx->SCSR SET_BIT(I2C_SCSR_DA);													//	Enable Slave Operation.
								pI2Cx->MCR SET_BIT(I2C_MCR_SFE);													//	Enable Slave Operation.
								break;
		case NO:		pI2Cx->SCSR CLR_BIT(1);			break;
	}
	
	
	pI2Cx->MCLKOCNT |= (0x10)<<0;															//	Set a timeout of 256 Clk cycles for clock stretching.
	pI2Cx->MIMR SET_BIT(I2C_MIM_CLKIM);												//	Enable Interrupt for Clock Timeout
	
}



/******************************************************************************************************************
* @I2CInit2()																																																			*
* @brief				- Initialize an I2C Module.																																				*
* @pI2CHandle		- Pointer to the I2C Handle.																																			*
* @return				- Nothing.																																												*
******************************************************************************************************************/
void I2CInit2(I2CHandle* pI2CHandle)
{
	uint8_t I2Cx, SpeedMode, ACKControl, UseAsSlave;
	uint32_t ClkSpeed;
	
	I2Cx				= pI2CHandle->I2Cx;
	SpeedMode		= pI2CHandle->SpeedMode;
	ClkSpeed 		= pI2CHandle->ClkSpeed;
	ACKControl	= pI2CHandle->ACKControl;
	UseAsSlave	= pI2CHandle->UseAsSlave;
	
	
	uint8_t Error = I2CClockControl(I2Cx, ENABLE);						//	Step 1 of section 16.4: Enable clock to the module and get error code.
	
	if(Error)		return;																				//	Break out of the function in case of an error.
	
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	pI2CHandle->pI2Cx = pI2Cx;
	
	uint8_t I2C_SCL_PIN = GetSCLPin(I2Cx);
	uint8_t I2C_SDA_PIN = GetSDAPin(I2Cx);
	
	uint8_t I2C_SCL_PIN_NUM = getPinNumber(I2C_SCL_PIN);
	uint8_t I2C_SDA_PIN_NUM = getPinNumber(I2C_SDA_PIN);
	
	GPIO_reg* pGPIO = getPortAddr(I2C_SCL_PIN, APB_BUS);
	
	
	GPIO_ClockControl(getPortName(I2C_SCL_PIN), ENABLE);			//	Step 2 of section 16.4
	
	pGPIO->GPIO_AFSEL SET_BIT( I2C_SCL_PIN_NUM );							//	Step 3 of section 16.4
	pGPIO->GPIO_AFSEL SET_BIT( I2C_SDA_PIN_NUM );
	
	pGPIO->GPIO_ODR SET_BIT( I2C_SDA_PIN_NUM );								//	Step 4 of section 16.4
	pGPIO->GPIO_ODR CLR_BIT( I2C_SCL_PIN_NUM );								//	Also see section 16.3 (Pg 999)
	
	pGPIO->GPIO_PUR SET_BIT( I2C_SCL_PIN_NUM );								//	Enable internal pull up resistor for SCL and SDA signals.
	pGPIO->GPIO_PUR SET_BIT( I2C_SDA_PIN_NUM );
	
	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SCL_PIN_NUM);							//	Step 5 of section 16.4	(The bit positions are cleared first and
	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SDA_PIN_NUM);							//													 then set appropriately)
	
	pGPIO->GPIO_PCTL |= (0x3<<(4*I2C_SCL_PIN_NUM));
	pGPIO->GPIO_PCTL |= (0x3<<(4*I2C_SDA_PIN_NUM));
	
	//pI2Cx->MCR SET_BIT(I2C_MCR_MFE);													//	Step 6 of section 16.4
	
	/*Step7 : Set desired spd mode & clock speed*/
	switch(SpeedMode)																					//	Enable/Disable High speed mode
	{
		case I2C_SPEED_MODE_HS: pI2Cx->MTPR SET_BIT( I2C_MTPR_HSE );
														pI2Cx->MCS	SET_BIT( I2C_MCS_HS );							break;
		default:								pI2Cx->MTPR CLR_BIT( I2C_MTPR_HSE );
														pI2Cx->MCS	CLR_BIT( I2C_MCS_HS );							break;
	}
	
	uint8_t TimerPRD = ( SYS_CLK/(20*ClkSpeed) ) - 1;					//	Timer Period
	
	pI2Cx->MTPR |= TimerPRD<<I2C_MTPR_TPR;										//	Step 7 of section 16.4
	
	switch(ACKControl)																				//	Enable/Disable Auto ACK
	{
		case I2C_AUTO_ACK_ENABLE:		pI2Cx->MCS SET_BIT( I2C_MCS_ACK );
		case I2C_AUTO_ACK_DISABLE:	pI2Cx->MCS CLR_BIT( I2C_MCS_ACK );
	}
	
	switch(UseAsSlave)
	{
		case YES:		pI2Cx->SCSR SET_BIT(1);			break;
		case NO:		pI2Cx->SCSR CLR_BIT(1);			break;
	}
	
	pI2Cx->SOAR |= ( (pI2CHandle->MasterAddress)<<0 );				//	Set Master's Own Address
	
	pI2Cx->MCLKOCNT |= (0x10)<<0;															//	Set a timeout of 256 Clk cycles for clock stretching.
	
	/* Step 8 and further are for sending data. They will be implemented in the send data api */
}



/******************************************************************************************************************
* @I2CMasterSendData()																																														*
* @brief					-	Send data over an I2C Module in Master mode.																									*
* @pI2CHandle			-	Pointer to the handle structure of I2C Module.																								*
*	@SlaveAddress		-	Address of the device to which data should be sent.																						*
*	@TxBuf					-	Pointer to the data buffer.																																		*
*	@Len						-	Length of the data (in bytes), i.e., the no. of 8 bit packets that are to be sent.						*
* @return					-	Error Code( 1 if transmission error has occured )																							*
******************************************************************************************************************/
uint8_t I2CMasterSendData(I2CHandle* pI2CHandle, uint8_t SlaveAddress, uint8_t* TxBuf, uint8_t Len)
{
	// Verify the steps from figure 16-10 (Pg. 1010)
	I2C_reg* pI2Cx = pI2CHandle->pI2Cx;
	
	pI2Cx->MCR SET_BIT( I2C_MCR_MFE );
	
	pI2Cx->MSA &= 0xFFFFFF00;									//	Step 8 of section 16.4
	pI2Cx->MSA |= ( SlaveAddress<<0 );
	
	uint8_t Data = *TxBuf;
	pI2Cx->MDR |= Data;												//	Step 9 of section 16.4
	
	pI2Cx->MCS SET_BIT( I2C_MCS_ACK );
	pI2Cx->MCS CLR_BIT( I2C_MCS_STOP );
	pI2Cx->MCS SET_BIT( I2C_MCS_START );
	pI2Cx->MCS SET_BIT( I2C_MCS_RUN );
	while(pI2Cx->MCS & 0x1);									//	Wait until the transmission completes.
	if(pI2Cx->MCS & 0x2)				return 1;			//	Return 1 in case of an error.
	TxBuf++;
	Len--;
	
	while(Len>0)
	{
		Data = *TxBuf;
		pI2Cx->MDR |= Data;											//	Step 9 of section 16.4
		
		while(pI2Cx->MCS & 0x1);								//	Wait until the transmission completes.
		if(pI2Cx->MCS & 0x2)				return 1;		//	Return 1 in case of an error.
		
		pI2Cx->MCS CLR_BIT( I2C_MCS_START );
		TxBuf++;
		Len--;
	}
	
	pI2Cx->MCS CLR_BIT( I2C_MCS_START );
	pI2Cx->MCS SET_BIT( I2C_MCS_RUN );
	pI2Cx->MCS SET_BIT( I2C_MCS_STOP );
	
	while(pI2Cx->MCS & 0x1);									//	Wait until the controller is busy
	
	return 0;																	//	Return 0 if the transmission was successful.
}

uint8_t I2CMasterSendData2(uint8_t I2Cx, uint8_t SlaveAddress, uint8_t* TxBuf, uint8_t Len)
{
	// Verify the steps from figure 16-10 (Pg. 1010)
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	
	
	pI2Cx->MSA &= 0xFFFFFF00;													//	Step 8 of section 16.4
	pI2Cx->MSA |= ( SlaveAddress<<0 );
	
	uint8_t Data = *TxBuf;
	pI2Cx->MDR |= Data;
	
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );
	
	pI2Cx->MCS = 0x00000003;
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );				//	Wait until the transmission completes.
	if(pI2Cx->MCS & 0x2)				return 1;							//	Return 1 in case of an error.
	TxBuf++;
	Len--;
	
	while(Len>0)
	{
		Data = *TxBuf;
		pI2Cx->MDR |= Data;
		
		while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );			//	Wait until the transmission completes.
		if(pI2Cx->MCS & 0x2)				return 1;						//	Return 1 in case of an error.
		
		pI2Cx->MCS = 0x00000001;
		TxBuf++;
		Len--;
	}
	
	pI2Cx->MCS = 0x00000005;
	
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );				//	Wait while the controller is busy
	
	return 0;																					//	Return 0 if the transmission was successful.
}



/******************************************************************************************************************
* @I2CMasterSendByte()																																														*
* @brief					-	Send a single byte over an I2C Module in Master mode.																					*
* @I2Cx						-	Name of the I2C module.																																				*
*	@SlaveAddress		-	Address of the device to which data should be sent.																						*
*	@Data						-	Data Byte that is to be sent.																																	*
* @return					-	Error Code( 1 if transmission error has occured )																							*
******************************************************************************************************************/
uint8_t I2CMasterSendByte(uint8_t I2Cx, uint8_t SlaveAddress, uint8_t Data)
{
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	
	
	pI2Cx->MSA &= 0xFFFFFF00;
	pI2Cx->MSA |= SlaveAddress<<0;
	pI2Cx->MSA |= 0x68;
	
	pI2Cx->MDR |= Data;
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );
	
	pI2Cx->MCS = 0x00000007;
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) && !GET_BIT(pI2Cx->MCS,I2C_MCS_CLKTO) );
	
	if( GET_BIT(pI2Cx->MCS, I2C_MCS_ERROR) )		return 1;			//	Check error bit and return 1 if error has occured.
	
	return 0;
}



/******************************************************************************************************************
* @I2CMasterRecvData()																																														*
* @brief					-	Recevie a single byte over an I2C Module in Master mode.																			*
* @I2Cx						-	Name of the I2C module.																																				*
*	@SlaveAddress		-	Address of the device from which data should be received.																			*
*	@RxBuf					-	Pointer to buffer where the received data should be stored.																		*
*	@Len						-	Length of data( no of data "bytes") that is to be received.																		*
* @return					-	Error Code( 1 if transmission error has occured )																							*
******************************************************************************************************************/
uint8_t I2CMasterRecvData(uint8_t I2Cx, uint8_t SlaveAddress, uint8_t* RxBuf, uint8_t Len)
{
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	
	pI2Cx->MSA &= 0xFFFFFF00;
	pI2Cx->MSA |= SlaveAddress<<0;
	
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );
	
	pI2Cx->MCS = 0x0000000B;
	
	while(Len>0)
	{
		while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );
		if( GET_BIT(pI2Cx->MCS, I2C_MCS_ERROR) )			//	Check error bit and return 1 if error has occured.
		{
			//if( !GET_BIT(pI2Cx->MCS, I2C_ARBLOST) )	//	See flowchart on Figure 16-11 for this step.
			if( !GET_BIT(pI2Cx->MCS, I2C_MCS_ARBLOST) )
				pI2Cx->MCS = 0x00000004;
			
			return 1;
		}
		*RxBuf = pI2Cx->MDR;
		
		RxBuf++;
		Len--;
		
		pI2Cx->MSA = 0x00000009;
	}
	return 0;
}



/******************************************************************************************************************
* @I2CMasterRecvByte()																																														*
* @brief					-	Recevie a single byte over an I2C Module in Master mode.																			*
* @I2Cx						-	Name of the I2C module.																																				*
*	@SlaveAddress		-	Address of the device from which data should be received.																			*
*	@RxByte					-	Pointer to the variable where the received byte should be stored.															*
* @return					-	Error Code( 1 if transmission error has occured )																							*
******************************************************************************************************************/
uint8_t I2CMasterRecvByte(uint8_t I2Cx, uint8_t SlaveAddress, uint8_t* RxByte)
{
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	uint8_t RxData;
	
	pI2Cx->MSA &= 0xFFFFFF00;
	pI2Cx->MSA |= SlaveAddress<<0;
	
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );
	
	pI2Cx->MCS = 0x00000007;
	
	while( GET_BIT(pI2Cx->MCS,I2C_MCS_BUSY) );
	if( GET_BIT(pI2Cx->MCS, I2C_MCS_ERROR) )		return 1;			//	Check error bit and return 1 if error has occured.
	
	RxData = pI2Cx->MDR;
	
	*RxByte = RxData;
	
	return 0;
}



/******************************************************************************************************************
* @I2CDeInit()																																																		*
* @brief				-	Reset and turn off an I2C Module.																																*
* @I2Cx					-	Name of the I2C module.																																					*
******************************************************************************************************************/
void I2CDeInit(uint8_t I2Cx)
{
	SYSCTL->SRI2C SET_BIT( (I2Cx-10) );				//	Reset the I2C Module.
	SYSCTL->SRI2C CLR_BIT( (I2Cx-10) );
	
	I2CClockControl(I2Cx,DISABLE);
}



/******************************************************************************************************************
*	@I2CGetAddress()																																																*
* @I2Cx		-	Name of the I2C module.																																								*
*	@return	-	Module Access Pointer of the given I2C Module.																												*
*	@Note		-	If the given i2c module is invalid, this function returns the pointer to I2C0. Double check the name	*
*						if an unexpected behaviour is observed.																																*
******************************************************************************************************************/
I2C_reg* I2CGetAddress(uint8_t I2Cx)
{
	switch(I2Cx)
	{
		case I2C0:		return pI2C0;
		case I2C1:		return pI2C1;
		case I2C2:		return pI2C2;
		case I2C3:		return pI2C3;
	}
	
	return pI2C0;
}



/******************************************************************************************************************
* @GetSCLPin()																																																		*
* @I2Cx		-	I2C Module Name.																																											*
* @return	-	SCL Pin of the given I2C Module.																																			*
*	@Note		-	If the given i2c module is invalid, this function returns the SCL pin of I2C0. Double check the name	*
*						if an unexpected behaviour is observed.																																*
******************************************************************************************************************/
uint8_t GetSCLPin(uint8_t I2Cx)
{
	switch(I2Cx)
	{
		case I2C0:		return I2C0_SCL_PIN;
		case I2C1:		return I2C1_SCL_PIN;
		case I2C2:		return I2C2_SCL_PIN;
		case I2C3:		return I2C3_SCL_PIN;
	}
	
	return I2C0_SCL_PIN;
}



/******************************************************************************************************************
* @GetSDAPin()																																																		*
* @I2Cx		-	I2C Module Name.																																											*
* @return	-	SDA Pin of the given I2C Module.																																			*
*	@Note		-	If the given i2c module is invalid, this function returns the SDA pin of I2C0. Double check the name	*
*						if an unexpected behaviour is observed.																																*
******************************************************************************************************************/
uint8_t GetSDAPin(uint8_t I2Cx)
{
	switch(I2Cx)
	{
		case I2C0:		return I2C0_SDA_PIN;
		case I2C1:		return I2C1_SDA_PIN;
		case I2C2:		return I2C2_SDA_PIN;
		case I2C3:		return I2C3_SDA_PIN;
	}
	
	return I2C0_SDA_PIN;
}

