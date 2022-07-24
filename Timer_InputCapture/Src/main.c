#include <stm32f4xx.h>
#include <stdio.h>
#include "delay.h"
#include "uart2.h"
#include "timer2.h"
#include "timer5.h"
#include "timer3.h"

#define SR_CC1IF	(1U << 1)
uint16_t timeperiod = 0 ;
int main(void)
{
	uart2_init_transmitter();
	timer2_ctc_init();
	timer_InputCaptureMode();
	while(1)
	{
		while(!(TIM3->SR & SR_CC1IF)){}
		timeperiod = TIM3->CCR1;
		//TIM3->SR &= ~SR_CC1IF;
		printf("Time: %d\r\n",timeperiod);
	}
}

