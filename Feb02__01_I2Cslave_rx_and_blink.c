#include "TM4C123xx.h"


int main(void)
{
	UseLEDs();
	
	
	while(1)
	{
	}
	return 0;
}

void I2C1_Handler(void)
{
	if( GET_BIT(pI2C1->SMIS,I2C_SMIS_DATA) )
	{
		// pick up data from here.
	}
}