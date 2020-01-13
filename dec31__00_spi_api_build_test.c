#include "TM4C123xx.h"
//#include "TM4C123xxGPIO_DRIVER.h"
//#include "GPIO_PIN_NAMES.h"
//#include "TM4C123xxSSI_DRIVER.h"

int main(void)
{
	SSIStart(SSI0,SSI_Slave_Mode_OutDis);
	
	while(1)
	{
	}
	return 0;
}
