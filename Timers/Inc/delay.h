/*
 * delay.h
 *
 *  Created on: Sep 17, 2022
 *      Author: kartik.iot
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stm32f401xe.h>

void _delay_us(int time_ms);
void _delay_ms(int time_ms);

#endif /* DELAY_H_ */
