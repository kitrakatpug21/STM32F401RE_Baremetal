/*
 * timer2.h
 *
 *  Created on: 26-Jun-2022
 *      Author: kartik.iot
 */

#ifndef TIMER2_H_
#define TIMER2_H_

#include <stm32f4xx.h>

void timer2_ctc_init(void);
void timer2_pwm_init(void);
void timer_InputCaptureMode(void);
#endif /* TIMER2_H_ */
