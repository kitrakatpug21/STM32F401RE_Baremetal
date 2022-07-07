#include <stm32f4xx.h>
#include "delay.h"

//USART2 -> APB1
//USART2-> TX -> PA2 (AF07)

#define GPIOAEN		(1U << 0)
#define USART2EN	(1U << 17)

int main(void)
{
	/*ENABLE THE AHB and APB Buses*/
	RCC -> AHB1ENR |= GPIOAEN;
	RCC -> APB1ENR |= USART2EN;

	/*GPIOA Mode Setup*/
	GPIOA -> MODER |= (1U<<5);
	GPIOA -> MODER &= ~(1U<<4);

	/*GPIOA Alternate Functionality Mode Setup*/
	GPIOA -> AFR[0] |= (1U << 8)|(1U<<9)|(1U<<10);
	GPIOA -> AFR[0] &= ~(1U<<11);

	/* USART BAUD Rate SETUP */
	USART2 -> BRR = ((0x0068<<4) + 0x0003);// 9600 Baud Setup

	/* USART CR1 Setup */
	USART2 -> CR1 |= (1<<3);//TE

	//USART2 -> ////// PARITY

	/*ENABLE THE USART PROTOCOL*/
	USART2 -> CR1 |= (1U<<13); // USART ENABLE

	USART2 -> DR = 'a';
	while(!(USART2 -> SR & (1U<<7)));

	USART2 -> DR = 'p';
	while(!(USART2 -> SR & (1U<<7)));

	USART2 -> DR = 'p';
	while(!(USART2 -> SR & (1U<<7)));

	USART2 -> DR = 'l';
	while(!(USART2 -> SR & (1U<<7)));

	USART2 -> DR = 'e';
	while(!(USART2 -> SR & (1U<<7)));

}
