#include <stm32f4xx.h>
#include "delay.h"
#include "timer2.h"
#include "timer5.h"

int main(void)
{
	timer2_pwm_init();
	timer5_pwm_init();
	while(1){}
}

