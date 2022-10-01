#include<TM4C123.h>

void timer0a_delay(int ms);
void timer1a_pwm(int duty_cycle);
void timer2a_pwm(int duty_cycle);
void timer3a_pwm(int duty_cycle);

int main()
{
	SYSCTL->RCGCTIMER |= 0x0F;	//enable clock for Timer 0-3
	
	SYSCTL->RCGCGPIO |= (1<<1);      /* enable clock to PORTB  */
	
	GPIOB->DIR |= (1<<4);   /* set PB4 an output pin */
	GPIOB->DEN |= (1<<4);    /* set PB4 a digital pin */
	GPIOB->AFSEL |= (1<<4);  /* enable alternate function on PB4 */
	GPIOB->PCTL &= ~0x000F0000;  /* configure PB4 as T1CCP0 pin */
	GPIOB->PCTL |= 0x00070000;

	GPIOB->DIR |= (1<<0);   /* set PB0 an output pin */
	GPIOB->DEN |= (1<<0);    /* set PB0 a digital pin */
	GPIOB->AFSEL |= (1<<0);  /* enable alternate function on PB0 */
	GPIOB->PCTL &= ~0x0000000F;  /* configure PB0 as T2CCP0 pin */
	GPIOB->PCTL |= 0x00000007;
	
	GPIOB->DIR |= (1<<2);   /* set PB2 an output pin */
	GPIOB->DEN |= (1<<2);    /* set PB2 a digital pin */
	GPIOB->AFSEL |= (1<<2);  /* enable alternate function on PB2 */
	GPIOB->PCTL &= ~0x00000F00;  /* configure PB2 as T3CCP0 pin */
	GPIOB->PCTL |= 0x00000700;
	
	int i = 0;
	int j = 0;
	int k = 0;
	while (1)
	{
		timer1a_pwm(i);
		timer2a_pwm(j);
		timer3a_pwm(k);
		i++;
		j++;j++;
		k++;k++;k++;
		if (i>99) i = 0;
		if (j>99) j = 0;
		if (k>99) k = 0;
		timer0a_delay(200);
	}
}

void timer1a_pwm(int duty_cycle) //duty cycle range: 0 - 100 %
{
	TIMER1->CTL |= 0x0;						//disable timer before initialization
	TIMER1->CFG = 0x4;						//select 16-bit configuration
	TIMER1->TAMR |= (1 << 3);			//TAAMS set to 0x1 to enable PWM mode
	TIMER1->TAMR &= ~(1UL << 2);	//TACMR reset to 0 for Edge Count Mode
	TIMER1->TAMR |= (2 << 0);			//TAMR set to 0x2 for periodic timer mode
	TIMER1->TAILR = 16000 - 1;		// 1ms period | interval load value register
	TIMER1->TAMATCHR = 160 * duty_cycle;	// cut-off edge to control PWM duty cycle
	TIMER1->CTL |= 0x1;						//enable timer to start counting after initializtion
}

void timer2a_pwm(int duty_cycle) //duty cycle range: 0 - 100 %
{
	TIMER2->CTL |= 0x0;						//disable timer before initialization
	TIMER2->CFG = 0x4;						//select 16-bit configuration
	TIMER2->TAMR |= (1 << 3);			//TAAMS set to 0x1 to enable PWM mode
	TIMER2->TAMR &= ~(1UL << 2);	//TACMR reset to 0 for Edge Count Mode
	TIMER2->TAMR |= (2 << 0);			//TAMR set to 0x2 for periodic timer mode
	TIMER2->TAILR = 16000 - 1;		// 1ms period | interval load value register
	TIMER2->TAMATCHR = 160 * duty_cycle;	// cut-off edge to control PWM duty cycle
	TIMER2->CTL |= 0x1;						//enable timer to start counting after initializtion
}


void timer3a_pwm(int duty_cycle) //duty cycle range: 0 - 100 %
{
	TIMER3->CTL |= 0x0;						//disable timer before initialization
	TIMER3->CFG = 0x4;						//select 16-bit configuration
	TIMER3->TAMR |= (1 << 3);			//TAAMS set to 0x1 to enable PWM mode
	TIMER3->TAMR &= ~(1UL << 2);	//TACMR reset to 0 for Edge Count Mode
	TIMER3->TAMR |= (2 << 0);			//TAMR set to 0x2 for periodic timer mode
	TIMER3->TAILR = 16000 - 1;		// 1ms period | interval load value register
	TIMER3->TAMATCHR = 160 * duty_cycle;	// cut-off edge to control PWM duty cycle
	TIMER3->CTL |= 0x1;						//enable timer to start counting after initializtion
}

void timer0a_delay(int ms)
{
	
	TIMER0->CTL |= 0x0;		//disable timer 0 before initialization
	TIMER0->CFG = 0x0;		//select 32 bit configuration for timer 0
	TIMER0->TAMR = 0x1;		//configure timer A for one shot mode
	TIMER0->TAILR = 16000*ms - 1;	//timer A interval load value register
	TIMER0->ICR = 0x1;		//clear status flag
	TIMER0->CTL |= 0x1;		//enable timer 0 to start counting after initializtion
	while ((TIMER0->RIS & 0x1) == 0); //wait for the timeout flag
}
