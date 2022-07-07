/*
 * delay.c
 *
 *  Created on: 04-Jun-2022
 *      Author: kartik.iot
 */

#include "delay.h"


#define ENABLE 			(1U<<0)
#define TICKINT			(1U<<1)
#define CLKSOURCE		(1U<<2)
#define COUNTFLAG		(1U<<16)

#define F_CPU 			16000000UL
#define ONE_US_COUNT	F_CPU / 1000000UL
#define ONE_MS_COUNT	F_CPU / 1000UL
#define ONE_S_COUNT		F_CPU

void delay_ms(int delay)
{
	/* Setup the Reload Register Value */
	SysTick -> LOAD = ONE_MS_COUNT - 1;
	// we reduce one value as the counter travels from
	// reload value to zero
	/* Clear the current Value register */
	SysTick -> VAL = 0;
	/* Select the Clock Source */
	SysTick -> CTRL |= CLKSOURCE;	// Peripheral Clock
	// if external clock is used, use 0 in CLK SOURCE
	/* Enable the system Tick  */
	SysTick -> CTRL |= ENABLE;
	/* NOw we will wait for count flag to turn on */
	for(int i = 0; i<delay; i++)
	{
		while ((SysTick -> CTRL & COUNTFLAG) == 0);
	}
	// once count flag is generated, we stop the counter
	SysTick -> CTRL &= ~ENABLE;
}

void delay_us(int delay)
{
	/* Setup the Reload Register Value */
	SysTick -> LOAD = ONE_US_COUNT - 1;
	// we reduce one value as the counter travels from
	// reload value to zero
	/* Clear the current Value register */
	SysTick -> VAL = 0;
	/* Select the Clock Source */
	SysTick -> CTRL |= CLKSOURCE;	// Peripheral Clock
	// if external clock is used, use 0 in CLK SOURCE
	/* Enable the system Tick  */
	SysTick -> CTRL |= ENABLE;
	/* NOw we will wait for count flag to turn on */
	for(int i = 0; i<delay; i++)
	{
		while ((SysTick -> CTRL & COUNTFLAG) == 0);
	}
	// once count flag is generated, we stop the counter
	SysTick -> CTRL &= ~ENABLE;
}
void Systick_Interrupt_Init()
{
	/* Setup the Reload Register Value */
	SysTick -> LOAD = F_CPU - 1;
	// we reduce one value as the counter travels from
	// reload value to zero
	/* Clear the current Value register */
	SysTick -> VAL = 0;
	/* Select the Clock Source */
	SysTick -> CTRL |= CLKSOURCE|TICKINT;	// Peripheral Clock and TICKINT
	// if external clock is used, use 0 in CLK SOURCE
	/* Enable the system Tick  */
	SysTick -> CTRL |= ENABLE;
	/* NOw we will wait for count flag to turn on */
	//while ((SysTick -> CTRL & COUNTFLAG) == 0);
	// once count flag is generated, we stop the counter
	//SysTick -> CTRL &= ~ENABLE;
}
