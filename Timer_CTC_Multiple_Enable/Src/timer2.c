/*
 * timer2.c
 *
 *  Created on: 26-Jun-2022
 *      Author: kartik.iot
 */

#include <timer2.h>

void timer2_ctc_init(void)
{
	// enable clocks for GPIOA and TIMER2
	RCC -> AHB1ENR |= (1U<<0);//GPIOA
	RCC -> APB1ENR |= (1U<<0);//TIMER2

	// Set GPIOA PA1 mode to Alternate Func Mode
	GPIOA -> MODER |= (1U<<3);
	GPIOA -> MODER &= ~(1U<<2);

	// SET PA1 to AF01
	GPIOA -> AFR[0] |= (1U<<4);
	GPIOA -> AFR[0] &= ~(1U<<5);
	GPIOA -> AFR[0] &= ~(1U<<6);
	GPIOA -> AFR[0] &= ~(1U<<7);

	/* Disable the timer 2 for changes*/
	TIM2 -> CR1 &= ~(1<<0);
	/*Set prescaler value*/
	TIM2->PSC =  800 - 1 ;
	/*Set auto-reload value*/
	TIM2->ARR =  10000 - 1;
	/*Set output compare toggle mode*/
	TIM2->CCMR1 |= (1U<<13)|(1U<<12);
	/*Enable tim2 ch2 in compare mode*/
	TIM2->CCER |= (1U<<4);
	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 |= (1<<0);
}
