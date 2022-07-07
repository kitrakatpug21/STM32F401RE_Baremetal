#include <stm32f4xx.h>
#include "delay.h"
#include "timer5.h"
#include "timer2.h"
#include "timer3.h"
int main(void)
{
	timer5_ctc_init();
	timer2_ctc_init();
	timer3_ctc_init();
	while(1){}
}

