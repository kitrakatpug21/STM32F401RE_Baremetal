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
	TIM2->ARR =  1000 - 1;
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

#define CR1_CEN	(1U << 0)
#define TIM2EN	(1U << 0)
#define TIM3EN	(1U << 1)
#define GPIOAEN	(1U<<0)

void timer_InputCaptureMode(void)
{
	// enable the GPIOA clocks
	RCC->AHB1ENR |=GPIOAEN;
	/*Set PA5 mode to alternate function*/
	//GPIOA->MODER &= ~(1U<<10);
	//GPIOA->MODER |= (1U<<11);
	/*Set PA6 mode to alternate function*/
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);
	// setup the alternate functionality mode for TIM2 CH1 (AF01)
	//GPIOA -> AFR[0]	|= (1U << 20);
	// setup the alternate functionality mode for TIM3 CH1 (AF02)
	GPIOA -> AFR[0]	|= (1U << 25);
	// enable the APB_CLOCKS for timer 2
	//RCC -> APB1ENR |= TIM2EN;
	RCC -> APB1ENR |= TIM3EN;
	// set the prescalar
	//TIM2 -> PSC = 1600 - 1;
	TIM3 -> ARR = 65535;
	TIM3 -> PSC = 8000 - 1;// bcuz sampling freq must be greater than message freq
	// set the auto-reload value
	//TIM2 -> ARR = 100 - 1;
	// Mode setup for timer 2 to generate output compare
	// Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1 and
	// CC1 channel is configured as output.
	//TIM2 -> CCMR1 |= (1U << 5);
	//TIM2 -> CCMR1 |= (1U << 4);
	// input capture at timer 3 CH1
	TIM3 -> CCMR1 |= (1U << 0);
	// Enable the compare mode in Timer 2
	//TIM2 -> CCER |= (1U << 0);
	// Enable the capture mode in Timer 3
	TIM3 -> CCER |= (1U << 0);
	//clear the counter in tim2
	//TIM2-> CNT = 0;
	// Enable the timer
	//TIM2 -> CR1 |= CR1_CEN;
	TIM3 -> CR1 |= CR1_CEN;

}
