/*
 * uart2.c
 *
 *  Created on: 11-Jun-2022
 *      Author: kartik.iot
 */
#include "uart2.h"

#define GPIOAEN		(1U << 0)
#define USART2EN	(1U << 17)

void uart2_init_transmitter(void)
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
}

void uart2_init_receiver(void)
{
	/*ENABLE THE AHB and APB Buses*/
	RCC -> AHB1ENR |= GPIOAEN;
	RCC -> APB1ENR |= USART2EN;

	/*GPIOA Mode Setup*/
	GPIOA -> MODER |= (1U<<7);
	GPIOA -> MODER &= ~(1U<<6);

	/*GPIOA Alternate Functionality Mode Setup*/
	GPIOA -> AFR[0] |= (1U<<12)|(1U<<13)|(1U<<14);
	GPIOA -> AFR[0] &= ~(1U<<15);

	/* USART BAUD Rate SETUP */
	USART2 -> BRR = ((0x0068<<4) + 0x0003);// 9600 Baud Setup

	/* USART CR1 Setup */
	USART2 -> CR1 |= (1<<2);//RE

	//USART2 -> ////// PARITY

	/*ENABLE THE USART PROTOCOL*/
	USART2 -> CR1 |= (1U<<13); // USART ENABLE
}

void uart2_transmit(char ch)
{
	USART2 -> DR = ch;
	//load the data
	while(!(USART2 -> SR & (1U<<7)));
	// wait till transmission is pending
}

unsigned char uart2_receive(void)
{
	while(!(USART2 -> SR & (1U<<5)));
	// wait till reception is processing
	return (USART2 -> DR);
	//return the data
}

int __io_putchar(int ch)
{
	uart2_transmit(ch);
	return ch;
}
