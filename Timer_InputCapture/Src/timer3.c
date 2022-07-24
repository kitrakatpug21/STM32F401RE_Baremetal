/*
 * timer3.c
 *
 *  Created on: 26-Jun-2022
 *      Author: kartik.iot
 */
#include <timer3.h>

void timer3_ctc_init(void)
{
	// enable clocks for GPIOA and TIMER5
	RCC -> AHB1ENR |= (1U<<0);//GPIOA
	RCC -> APB1ENR |= (1U<<1);//TIMER3

	// Set GPIOA PA0 mode to Alternate Func Mode
	GPIOA -> MODER |= (1U<<13);
	GPIOA -> MODER &= ~(1U<<12);

	// SET PA0 to AF02
	GPIOA -> AFR[0] |= (1U<<25);
	GPIOA -> AFR[0] &= ~(1U<<24);
	GPIOA -> AFR[0] &= ~(1U<<26);
	GPIOA -> AFR[0] &= ~(1U<<27);

	/* Disable the timer 3 for changes*/
	TIM3 -> CR1 &= ~(1<<0);
	/*Set prescaler value*/
	TIM3->PSC =  800 - 1 ;
	/*Set auto-reload value*/
	TIM3->ARR =  10000 - 1;
	/*Set output compare toggle mode*/
	TIM3->CCMR1 |= (1U<<4)|(1U<<5);
	/*Enable tim5 ch1 in compare mode*/
	TIM3->CCER |= (1U<<0);
	/*Clear counter*/
	TIM3->CNT = 0;
	/*Enable timer*/
	TIM3->CR1 |= (1<<0);
}

void timer3_inputCapture_init(void)
{
	/*Enable clock access to GPIOA*/
	RCC -> AHB1ENR |= (1U<<0);

	/*Set PA6 mode to alternate function*/
	GPIOA -> MODER &= ~(1U<<12);
	GPIOA -> MODER |= (1U<<13);

	/*Set PA6 alternate function type to TIM3_CH1 (AF02)*/
	//SET THE AF MODE IN AFR register
	GPIOA -> AFR[0] &= ~(1U<<24);
	GPIOA -> AFR[0] |= (1U<<25);
	GPIOA -> AFR[0] &= ~(1U<<26);
	GPIOA -> AFR[0] &= ~(1U<<27);

	/*Enable clock access to tim3*/
	RCC -> APB1ENR |= (1U<<1);

	/*Set Prescaler*/
	TIM3 -> PSC = 800 - 1;

	/*Set CH1 to input capture*/
	TIM3 -> CCMR1 = (1U<<0);

	/*Set CH1 to capture at rising edge*/
	TIM3 -> CCER = (1U<<0);

	//TIM3 -> CCR1 = 0;

	/*Enable TIM3*/
	TIM3 -> CR1 = (1U<<0);
}
