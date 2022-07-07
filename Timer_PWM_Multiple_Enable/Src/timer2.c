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

void timer2_pwm_init(void)
{
	// enable clocks for GPIOA
	RCC -> AHB1ENR |= (1U<<0);//GPIOA
	//SET THE PA5 pin as AF-01
	GPIOA -> MODER |= (1U<<11);
	GPIOA -> MODER &= ~(1U<<10);
	//SET THE AF MODE IN AFR register
	GPIOA -> AFR[0] |= (1U<<20);
	GPIOA -> AFR[0] &= ~(1U<<21);
	GPIOA -> AFR[0] &= ~(1U<<22);
	GPIOA -> AFR[0] &= ~(1U<<23);

	// enable clocks for TIMER2
	RCC -> APB1ENR |= (1U<<0);//TIMER2
	/* Disable the timer 2 for changes*/
	TIM2 -> CR1 &= ~(1<<0);
	/*Set prescaler value*/
	TIM2->PSC = 320 - 1;
	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;
	/*Clear counter*/
	TIM2->CNT = 0;
	/*Set the Compare Value*/
	TIM2->CCR1 = 1000 - 1;
	/*Set PWM mode - 1*/
	TIM2->CCMR1 |= (1U<<5)|(1U<<6);
	/*Enable tim2 ch1 in PWM mode*/
	TIM2->CCER |= (1U<<0);
	/*Enable timer*/
	TIM2->CR1 |= (1<<0);
}
