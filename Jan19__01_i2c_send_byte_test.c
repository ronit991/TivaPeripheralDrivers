#include "TM4C123xx.h"

void blink(uint8_t pin);
void delay_s(void);
void delay_l(void);

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF2,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	
	I2CInit(I2C1,I2C_SPEED_MODE_STD,100000,I2C_AUTO_ACK_ENABLE, I2C_DONT_USE_AS_SLAVE);
	
	WriteToPin(PF3,PIN_SET);

	while(1)
	{
		uint8_t error = I2CMasterSendByte(I2C1, 0x68, 65);
		if(error)	break;
		
		delay_l();
		blink(PF1);
	}
	
	WriteToPin(PF3,PIN_RESET);
	WriteToPin(PF2,PIN_SET);
	while(1);
	
	return 0;
}

/**/
void I2C1_Handler(void)
{
	pI2C1->MCS = 0x00000004;			//	Generate a STOP Condition.
	pI2C1->MICR SET_BIT(1);				//	Clear the Clock Timeout Interrupt
	blink(PF2);
}

/*  */
void blink(uint8_t pin)
{
	WriteToPin(pin,PIN_SET);			delay_s();
	WriteToPin(pin,PIN_RESET);		delay_s();
}

void delay_s(void)
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<1000; j++);
}
void delay_l(void)
{
	for(int i = 0; i<35000; i++)
		for(int j = 0; j<1000; j++);
}
