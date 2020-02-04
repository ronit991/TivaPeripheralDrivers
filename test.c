#include "TM4C123xx.h"

int main(void)
{
	UseLEDs();
	
	while(1)
	{
		blink(LED_RED);
		blink(LED_BLUE);
		blink(LED_GREEN);
	}
	return 0;
}
