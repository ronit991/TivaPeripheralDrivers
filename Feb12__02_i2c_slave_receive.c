#include "TM4C123xx.h"

#define Hello (uint8_t)0x69
#define SlaveAddress (uint8_t)0x68


int main(void)
{
	UseLEDs();
	I2CSetSlaveAddress(I2C0, SlaveAddress);
	I2CInit(I2C0, I2C_SPEED_MODE_STD, 100000, I2C_AUTO_ACK_ENABLE, YES);
	uint8_t RxData = 0, PrevRx = 0;
	
	while(1)
	{
		if(RxData != PrevRx)
		{
			if(RxData != Hello)
			{
				TurnOff(LED_GREEN);
				TurnOn(LED_RED);
			}
			else
			{
				TurnOn(LED_GREEN);
				TurnOff(LED_RED);
			}
			PrevRx = RxData;
		}
		RxData = I2CSlaveRecvByte(I2C0);
	}
}
