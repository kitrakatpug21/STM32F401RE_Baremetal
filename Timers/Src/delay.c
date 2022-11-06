/*
 * delay.c
 *
 *  Created on: Sep 17, 2022
 *      Author: kartik.iot
 */

#include "delay.h"


#define COUNTFLAG		(1<<16)
#define CLKSOURCE 		(1<<2)
#define TICKINT			(1<<1)
#define ENABLE			(1<<0)

#define F_CPU 					16000000UL
#define DELAY_MS_COUNTER		(F_CPU / 1000)	 //16000
#define DELAY_US_COUNTER		(F_CPU / 1000000)// 16

void _delay_ms(int time_ms)
{
	SysTick -> CTRL |= CLKSOURCE; // external clock
	for (int repeat = 0; repeat < time_ms; repeat = repeat + 1)
	{
		SysTick -> LOAD = DELAY_MS_COUNTER;
		SysTick -> VAL = 0;
		SysTick -> CTRL |= ENABLE;
		while ((SysTick -> CTRL & COUNTFLAG) == 0)
		{
			// wait here till COUNTER reaches 0
		}
		// once reached,
		SysTick -> CTRL &= ~ENABLE;
	}
}

void _delay_us(int time_ms)
{
	SysTick -> CTRL |= CLKSOURCE; // external clock
	for (int repeat = 0; repeat < time_ms; repeat = repeat + 1)
	{
		SysTick -> LOAD = DELAY_US_COUNTER;
		SysTick -> VAL = 0;
		SysTick -> CTRL |= ENABLE;
		while ((SysTick -> CTRL & COUNTFLAG) == 0)
		{
			// wait here till COUNTER reaches 0
		}
		// once reached,
		SysTick -> CTRL &= ~ENABLE;
	}
}
