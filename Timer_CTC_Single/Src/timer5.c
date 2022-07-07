/*
 * timer5.c
 *
 *  Created on: 25-Jun-2022
 *      Author: kartik.iot
 */

#include <timer5.h>

void timer5_init(void)
{
	// enable clocks for GPIOA and TIMER5
	RCC -> AHB1ENR |= (1U<<0);
	RCC -> APB1ENR |= (1U<<3);

	// Set GPIOA PA0 mode to Alternate Func Mode
	GPIOA -> MODER |= (1U<<1);
	GPIOA -> MODER &= ~(1U<<0);

	// SET PA0 to AF02
	GPIOA -> AFR[0] |= (1U<<1);
	GPIOA -> AFR[0] &= ~(1U<<0);
	GPIOA -> AFR[0] &= ~(1U<<0);
	GPIOA -> AFR[0] &= ~(1U<<0);

	/* Diable the timer 5 for changes*/
	TIM5 -> CR1 &= ~(1<<0);
	/*Set prescaler value*/
	TIM2->PSC =  1600 - 1 ;  //  16 000 000 / 1 600 = 10 000
	/*Set auto-reload value*/
	TIM2->ARR =  10000 - 1;  // 10 000 / 10 000 = 1
	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}

