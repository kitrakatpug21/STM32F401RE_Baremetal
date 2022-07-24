/*
 * timer5.c
 *
 *  Created on: 25-Jun-2022
 *      Author: kartik.iot
 */

#include <timer5.h>

void timer5_ctc_init(void)
{
	// enable clocks for GPIOA and TIMER5
	RCC -> AHB1ENR |= (1U<<0);//GPIOA
	RCC -> APB1ENR |= (1U<<3);//TIMER5

	// Set GPIOA PA0 mode to Alternate Func Mode
	GPIOA -> MODER |= (1U<<1);
	GPIOA -> MODER &= ~(1U<<0);

	// SET PA0 to AF02
	GPIOA -> AFR[0] |= (1U<<1);
	GPIOA -> AFR[0] &= ~(1U<<0);
	GPIOA -> AFR[0] &= ~(1U<<2);
	GPIOA -> AFR[0] &= ~(1U<<3);

	/* Disable the timer 5 for changes*/
	TIM5 -> CR1 &= ~(1<<0);
	/*Set prescaler value*/
	TIM5->PSC =  800 - 1 ;
	/*Set auto-reload value*/
	TIM5->ARR =  10000 - 1;
	/*Set output compare toggle mode*/
	TIM5->CCMR1 |= (1U<<4)|(1U<<5);
	/*Enable tim5 ch1 in compare mode*/
	TIM5->CCER |= (1U<<0);
	/*Clear counter*/
	TIM5->CNT = 0;
	/*Enable timer*/
	TIM5->CR1 |= (1<<0);
}

void timer5_pwm_init(void)
{
	// enable clocks for GPIOA
	RCC -> AHB1ENR |= (1U<<0);//GPIOA
	//SET THE PA5 pin as AF-01
	GPIOA -> MODER |= (1U<<1);
	GPIOA -> MODER &= ~(1U<<0);
	//SET THE AF MODE IN AFR register
	GPIOA -> AFR[0] &= ~(1U<<0);
	GPIOA -> AFR[0] |= (1U<<1);
	GPIOA -> AFR[0] &= ~(1U<<2);
	GPIOA -> AFR[0] &= ~(1U<<3);

	// enable clocks for TIMER5
	RCC -> APB1ENR |= (1U<<3);//TIMER5
	/* Disable the timer 5 for changes*/
	TIM5 -> CR1 &= ~(1<<0);
	/*Set prescaler value*/
	TIM5->PSC = 320 - 1;
	/*Set auto-reload value*/
	TIM5->ARR = 10000 - 1;
	/*Clear counter*/
	TIM5->CNT = 0;
	/*Set the Compare Value*/
	TIM5->CCR1 = 3000 - 1;
	/*Set PWM mode - 1*/
	TIM5->CCMR1 |= (1U<<5)|(1U<<6)|(1U<<4);
	/*Enable tim2 ch1 in PWM mode*/
	TIM5->CCER |= (1U<<0);
	/*Enable timer*/
	TIM5->CR1 |= (1<<0);
}

