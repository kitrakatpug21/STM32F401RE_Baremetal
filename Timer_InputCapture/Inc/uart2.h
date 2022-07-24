/*
 * uart2.h
 *
 *  Created on: 11-Jun-2022
 *      Author: kartik.iot
 */

#ifndef UART2_H_
#define UART2_H_

#include <stm32f4xx.h>
#include <stdio.h>

void uart2_init_transmitter(void);// only transmitter
void uart2_init_receiver(void);	  // only receiver
void uart2_init_transceiver(void);// both tx and rx

void uart2_transmit(char ch);
unsigned char uart2_receive(void);

#endif /* UART2_H_ */
