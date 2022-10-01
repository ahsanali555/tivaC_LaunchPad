#include "TM4C123GH6PM.h"
int main()
{
  SYSCTL->RCGCGPIO |= 0x20;		// turn on bus clock for GPIOF
  GPIOF->DIR       |= 0x0E;		// set RBG pins as digital output pin
  GPIOF->DEN       |= 0x0E;		// Enable PF1-3 pinw as digital pin
	
	SysTick->LOAD = 15999999; // one second delay relaod value
	SysTick->CTRL = 7 ; // enable counter, interrupt and select system bus clock 
	SysTick->VAL  = 0; //initialize current value register 
   
	while (1)
	{
		//do nothing here
	}
}

// this routine will execute after every one second

void SysTick_Handler(void)
{
   GPIOF->DATA  ^= 0xE;  //toggle PF3 pin
  
}